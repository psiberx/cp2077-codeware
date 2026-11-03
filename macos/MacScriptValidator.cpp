// R15. Script validator layer and opcode handlers on Mac.
//
// A port of Codeware's src/App/Scripting/ScriptingService.cpp (the Windows file is unchanged):
//   OnValidateScripts   -> OnValidate           (Validate 0x21FBF90, full hook so the counts can be logged afterwards)
//   OnValidateProperty  -> OnValidateProperty   (ValidateProperty 0x21FCFB8, full hook)
//   OnValidateScriptType-> ValidateScriptType   (array recursion, leaf = CompareType 0x21FD144 called as a function)
//   OnValidateTypeName  -> MatchNames           (CompareTypeName is inlined on Mac, so its rules run at the leaves)
//   ScriptOpCodeNew/Cast-> same bodies, written into the opcode handler table (0x908B798) by PatchScriptOpCodes.
//
// Mac facts this file relies on (R14 static analysis, R15 re-checked):
//   ScriptBundle (2.5.0: +8 in front): classes DynArray at +0xD8 (entries, capacity, size), definitionsByName HashMap at +0x08.
//   ScriptClass (2.5.0): name +0x08, parent +0x48, properties +0x50 (capacity +0x58, size +0x5C), flags byte +0xD1 (bit1 importOnly,
//   bit2 abstract, bit4 struct). ScriptProperty: type +0xB8. ScriptType: name +0x08, innerType +0x48,
//   metaType +0x54. (2.3.1: classes +0xD0, definitionsByName +0x00, parent +0x20, properties +0x28/+0x30/+0x34, flags +0x89,
//   property type +0x90, innerType +0x20, metaType +0x2C.) EScriptType and ERTTIType values equal the SDK enums (the game's jump tables use them).
//   ScriptDefinition virtuals sit 8 bytes later than the Windows header comments (two destructor slots), which the
//   compiler already accounts for when the header is built for Mac (GetType 0x18, IsNative 0x38 match the game).
//   CBaseRTTIType::GetType is vtable +0x28, GetInnerType +0xC8 (same shift, again produced by the compiler).
//
// DIAG R15 marks the counters and logs that print only with CODEWARE_MAC_DIAG=1.

#include "MacDiag.hpp"
#include "MacR15.hpp"
#include "MacEngine.hpp"

#include "MacAddressResolver.hpp"

#include "Core/Hooking/HookingAgent.hpp"
#include "Red/Scripting.hpp"
#include "App/Scripting/VanillaApiCompat.hpp"

#include <atomic>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <map>
#include <mutex>
#include <set>
#include <string>

#include <mach/mach.h>
#include <mach/vm_map.h>
#include <unistd.h>

namespace
{
// ---- constants. The type names are the RTTI names set by RTTI_DEFINE_CLASS in App/Depot/ResourceReference.hpp
// and App/Engine/CurveData.hpp, plus the redResourceReferenceScriptToken alias. They are written out here so this
// file does not pull those headers (and their RTTI registrars) into a second translation unit.
constexpr auto kISerializable = Red::GetTypeName<Red::ISerializable>();
constexpr auto kIScriptable = Red::GetTypeName<Red::IScriptable>();

constexpr auto kResourceRef = Red::CName("ResourceRef");
constexpr auto kResourceAsyncRef = Red::CName("ResourceAsyncRef");
constexpr auto kResRefAlias = Red::CName("ResRef");
constexpr auto kCurveDataFloat = Red::CName("CurveDataFloat");
constexpr auto kCurveDataVector2 = Red::CName("CurveDataVector2");
constexpr auto kCurveDataVector3 = Red::CName("CurveDataVector3");
constexpr auto kCurveDataVector4 = Red::CName("CurveDataVector4");
constexpr auto kCurveDataHDRColor = Red::CName("CurveDataHDRColor");

// Game 2.5 declares CallbackSystemHandler.SetRunMode/SetLifetime with its own enums (same members and values as Codeware's).
constexpr auto kGameCallbackRunMode = Red::CName("gameCallbackRunMode");
constexpr auto kGameCallbackLifetime = Red::CName("gameCallbackLifetime");
constexpr auto kCallbackRunMode = Red::CName("CallbackRunMode");
constexpr auto kCallbackLifetime = Red::CName("CallbackLifetime");

constexpr char kResourceRefPrefix[] = "rRef:";
constexpr char kResourceAsyncRefPrefix[] = "raRef:";
constexpr char kCurveDataPrefix[] = "curveData:";

constexpr auto kInkWidgetLibraryResource = Red::CName("inkWidgetLibraryResource");
constexpr auto kGameuiBaseUIData = Red::CName("gameuiBaseUIData");
constexpr auto kScnChatter = Red::CName("scnChatter");
constexpr auto kAudioEventElement = Red::CName("audioAudioEventMetadataArrayElement");
constexpr auto kEntLODDefinition = Red::CName("entLODDefinition");

constexpr uintptr_t kOpcodeTableRva = 0x9A5C940;
constexpr uint8_t kOpNew = Raw::ScriptOpCodes::New;   // 48
constexpr uint8_t kOpCast = Raw::ScriptOpCodes::Cast; // 90

// ---- memory safety for the layout guard. The guard reads game memory through this before anything is
// dereferenced with plain pointers.
bool SafeCopy(const void* aSrc, void* aDst, size_t aSize)
{
    vm_size_t got = 0;
    return vm_read_overwrite(mach_task_self(), reinterpret_cast<vm_address_t>(aSrc), aSize,
                             reinterpret_cast<vm_address_t>(aDst), &got) == KERN_SUCCESS &&
           got == aSize;
}

template<typename T>
bool SafeRead(const void* aSrc, T& aOut)
{
    return SafeCopy(aSrc, &aOut, sizeof(T));
}

bool InGameImage(uint64_t aPtr)
{
    const auto base = static_cast<uint64_t>(Red::MacGameBase());
    return aPtr >= base && aPtr < base + 0x20000000ull;
}

bool PrintableName(Red::CName aName, std::string& aOut)
{
    if (!aName.hash)
    {
        return false;
    }
    const char* s = aName.ToString();
    if (!s || !*s)
    {
        return false;
    }
    for (size_t i = 0; i < 256; ++i)
    {
        const unsigned char c = static_cast<unsigned char>(s[i]);
        if (c == 0)
        {
            aOut.assign(s, i);
            return i > 0;
        }
        if (c < 0x20 || c > 0x7E)
        {
            return false;
        }
    }
    return false;
}

const char* NameStr(Red::CName aName)
{
    if (!aName.hash)
    {
        return "<none>";
    }
    const char* s = aName.ToString();
    return s ? s : "<?>";
}

// ---- name rules, the exact rules of ScriptingService::OnValidateTypeName.
enum class NameRule
{
    None,
    Wrapper, // ResourceRef -> rRef:, ResourceAsyncRef / ResRef -> raRef:
    Curve,   // the five CurveData wrappers -> curveData:
    Alias,   // 2.5: gameCallbackRunMode / gameCallbackLifetime -> CallbackRunMode / CallbackLifetime (counted with the wrappers)
};

NameRule MatchNames(Red::CName aScript, Red::CName aNative)
{
    if (!aScript.hash || !aNative.hash)
    {
        return NameRule::None;
    }

    if ((aScript == kGameCallbackRunMode && aNative == kCallbackRunMode) ||
        (aScript == kGameCallbackLifetime && aNative == kCallbackLifetime))
    {
        return NameRule::Alias;
    }
    if (aScript == kResourceRef)
    {
        const char* n = aNative.ToString();
        return n && std::strncmp(kResourceRefPrefix, n, sizeof(kResourceRefPrefix) - 1) == 0 ? NameRule::Wrapper
                                                                                          : NameRule::None;
    }
    if (aScript == kResourceAsyncRef || aScript == kResRefAlias)
    {
        const char* n = aNative.ToString();
        return n && std::strncmp(kResourceAsyncRefPrefix, n, sizeof(kResourceAsyncRefPrefix) - 1) == 0
                   ? NameRule::Wrapper
                   : NameRule::None;
    }
    if (aScript == kCurveDataFloat || aScript == kCurveDataVector2 || aScript == kCurveDataVector3 ||
        aScript == kCurveDataVector4 || aScript == kCurveDataHDRColor)
    {
        const char* n = aNative.ToString();
        return n && std::strncmp(kCurveDataPrefix, n, sizeof(kCurveDataPrefix) - 1) == 0 ? NameRule::Curve
                                                                                      : NameRule::None;
    }
    return NameRule::None;
}

// The script-side name the game compares for a type: ValidateProperty uses ScriptType.name for a Primitive and the
// inner definition's name for a Class; the CompareType leaf uses ScriptType.name. Try both for a Class.
NameRule MatchScriptType(const Red::ScriptType* aScript, Red::CBaseRTTIType* aNative, Red::CName* aMatchedName = nullptr)
{
    if (!aScript || !aNative)
    {
        return NameRule::None;
    }

    const auto nativeName = aNative->GetName();

    auto rule = MatchNames(aScript->name, nativeName);
    if (rule != NameRule::None)
    {
        if (aMatchedName)
        {
            *aMatchedName = aScript->name;
        }
        return rule;
    }

    if (aScript->metaType == Red::EScriptType::Class && aScript->innerType)
    {
        rule = MatchNames(aScript->innerType->name, nativeName);
        if (rule != NameRule::None && aMatchedName)
        {
            *aMatchedName = aScript->innerType->name;
        }
        return rule;
    }

    return NameRule::None;
}

// ---- DIAG R15 counters.
struct ValidateStats
{
    std::atomic<uint32_t> validateCalls{0};
    std::atomic<uint64_t> propCalls{0};
    std::atomic<uint64_t> arrayCalls{0};
    std::atomic<uint64_t> arrayOverride{0}; // the array path accepted what the game's own check rejected
    std::atomic<uint64_t> arrayRegress{0};  // the array path rejected what the game's own check accepted (kept true)
    std::atomic<uint64_t> bitfieldOverride{0};
    std::atomic<uint64_t> wrapperOverride{0};
    std::atomic<uint64_t> curveOverride{0};
    std::atomic<uint64_t> enumMismatch{0};
    std::atomic<uint64_t> stillRejected{0};
    std::atomic<uint32_t> loggedArray{0};
    std::atomic<uint32_t> loggedBitfield{0};
    std::atomic<uint32_t> loggedWrapper{0};
    std::atomic<uint32_t> loggedCurve{0};
    std::atomic<uint32_t> loggedEnum{0};
};
ValidateStats g_stats;

// R17. The property the game's validator was last asked about, for the crash report.
std::atomic<Red::ScriptProperty*> g_lastScriptProp{nullptr};
std::atomic<Red::CProperty*> g_lastNativeProp{nullptr};

std::mutex g_statsLock;
std::map<std::string, uint32_t> g_bitfieldNative; // "scriptType -> nativeType" for the bitfield rule
std::map<std::string, uint32_t> g_enumNative;     // native Enum vs script Primitive, still rejected

void PropNames(const Red::ScriptProperty* aProp, char* aOut, size_t aSize)
{
    const char* cls = "<?>";
    if (aProp && aProp->parent)
    {
        cls = NameStr(aProp->parent->name);
    }
    std::snprintf(aOut, aSize, "%s.%s", cls, aProp ? NameStr(aProp->name) : "<?>");
}

// The leaf of OnValidateScriptType: the game's CompareType, then the CompareTypeName rules.
bool ValidateLeaf(Red::CBaseRTTIType* aNative, Red::ScriptType* aScript, NameRule& aRule)
{
    if (Raw::ScriptValidator::CompareType(aNative, aScript))
    {
        return true;
    }

    aRule = MatchScriptType(aScript, aNative);
    return aRule != NameRule::None;
}

// Port of ScriptingService::OnValidateScriptType. The array element type is read with the virtual GetInnerType
// (the Windows code reads the innerType field).
bool ValidateScriptType(Red::CBaseRTTIType* aNative, Red::ScriptType* aScript, NameRule& aRule)
{
    if (!aNative || !aScript)
    {
        return false;
    }

    if (aScript->metaType == Red::EScriptType::DynArray)
    {
        if (aNative->GetType() == Red::ERTTIType::Array)
        {
            auto* nativeInner = reinterpret_cast<Red::CRTTIBaseArrayType*>(aNative)->GetInnerType();
            auto* scriptInner = reinterpret_cast<Red::ScriptType*>(aScript->innerType);
            return ValidateScriptType(nativeInner, scriptInner, aRule);
        }
        return false;
    }

    if (aScript->metaType == Red::EScriptType::StaticArray)
    {
        const auto type = aNative->GetType();
        if (type == Red::ERTTIType::StaticArray || type == Red::ERTTIType::NativeArray ||
            type == Red::ERTTIType::FixedArray)
        {
            auto* nativeInner = reinterpret_cast<Red::CRTTIBaseArrayType*>(aNative)->GetInnerType();
            auto* scriptInner = reinterpret_cast<Red::ScriptType*>(aScript->innerType);
            return ValidateScriptType(nativeInner, scriptInner, aRule);
        }
        return false;
    }

    return ValidateLeaf(aNative, aScript, aRule);
}

// ---- layout guard. Reads with SafeRead; nothing is written until every check passes.
struct LayoutResult
{
    bool ok = false;
    std::string which;
    uint32_t classCount = 0;
};

LayoutResult CheckLayout(Red::ScriptBundle* aBundle)
{
    LayoutResult r;
    auto fail = [&r](const std::string& aWhich) {
        r.ok = false;
        r.which = aWhich;
        return r;
    };

    if (!aBundle)
    {
        return fail("bundle is null");
    }

    uint64_t entries = 0;
    uint32_t capacity = 0;
    uint32_t size = 0;
    // DynArray's members are private since SDK 1.0 (RED4ext.SDK #180): read the three words by their ABI offsets (00, 08, 0C).
    const auto* classesRaw = reinterpret_cast<const uint8_t*>(&aBundle->classes);
    if (!SafeRead(classesRaw + 0x00, entries) || !SafeRead(classesRaw + 0x08, capacity) || !SafeRead(classesRaw + 0x0C, size))
    {
        return fail("classes unreadable (+0xD8)");
    }
    if (size < 1 || size > 200000 || capacity < size || entries == 0 || (entries & 7) != 0)
    {
        char buf[96];
        std::snprintf(buf, sizeof(buf), "classes.size=%u capacity=%u entries=0x%llx", size, capacity,
                      static_cast<unsigned long long>(entries));
        return fail(buf);
    }
    r.classCount = size;

    const uint32_t sample = size < 5 ? size : 5;
    for (uint32_t i = 0; i < sample; ++i)
    {
        uint64_t ptr = 0;
        if (!SafeRead(reinterpret_cast<const void*>(entries + 8ull * i), ptr) || ptr == 0 || (ptr & 7) != 0)
        {
            return fail("classes[" + std::to_string(i) + "] pointer");
        }

        uint64_t vtable = 0;
        uint64_t nameHash = 0;
        uint64_t parent = 0;
        uint8_t flags = 0;
        if (!SafeRead(reinterpret_cast<const void*>(ptr), vtable) || !InGameImage(vtable))
        {
            return fail("classes[" + std::to_string(i) + "] vtable");
        }
        if (!SafeRead(reinterpret_cast<const void*>(ptr + 0x08), nameHash))
        {
            return fail("classes[" + std::to_string(i) + "] name unreadable");
        }
        std::string name;
        if (!PrintableName(Red::CName(nameHash), name))
        {
            return fail("classes[" + std::to_string(i) + "] name is not a printable string");
        }
        if (!SafeRead(reinterpret_cast<const void*>(ptr + 0x48), parent) || (parent != 0 && (parent & 7) != 0))
        {
            return fail("classes[" + std::to_string(i) + "] parent (+0x48)");
        }
        if (!SafeRead(reinterpret_cast<const void*>(ptr + 0xD1), flags))
        {
            return fail("classes[" + std::to_string(i) + "] flags (+0xD1)");
        }
        uint32_t propCapacity = 0;
        uint32_t propSize = 0;
        if (!SafeRead(reinterpret_cast<const void*>(ptr + 0x58), propCapacity) ||
            !SafeRead(reinterpret_cast<const void*>(ptr + 0x5C), propSize) || propSize > propCapacity ||
            propSize > 1000000)
        {
            return fail("classes[" + std::to_string(i) + "] properties (+0x50)");
        }

        // GetType() is the third virtual after the two destructors (vtable +0x18) and must say Class.
        uint64_t getType = 0;
        if (!SafeRead(reinterpret_cast<const void*>(vtable + 0x18), getType) || !InGameImage(getType))
        {
            return fail("classes[" + std::to_string(i) + "] vtable GetType slot");
        }
        auto* def = reinterpret_cast<Red::ScriptDefinition*>(ptr);
        if (def->GetType() != Red::EScriptDefinition::Class)
        {
            return fail("classes[" + std::to_string(i) + "] GetType is not Class");
        }
    }

    // definitionsByName must find ISerializable and IScriptable. Check the table header first.
    uint64_t indexTable = 0;
    uint32_t mapSize = 0;
    uint32_t mapCapacity = 0;
    if (!SafeRead(&aBundle->definitionsByName, indexTable) ||
        !SafeRead(reinterpret_cast<const uint8_t*>(&aBundle->definitionsByName) + 8, mapSize) ||
        !SafeRead(reinterpret_cast<const uint8_t*>(&aBundle->definitionsByName) + 12, mapCapacity) || indexTable == 0 ||
        mapSize == 0 || mapCapacity < mapSize)
    {
        return fail("definitionsByName header (+0x08)");
    }

    if (!aBundle->definitionsByName.Get(kISerializable))
    {
        return fail("definitionsByName does not find ISerializable");
    }
    if (!aBundle->definitionsByName.Get(kIScriptable))
    {
        return fail("definitionsByName does not find IScriptable");
    }

    r.ok = true;
    return r;
}

// Looks a definition up with null checks (Windows dereferences the result unchecked).
Red::ScriptClass* FindClassDef(Red::ScriptBundle* aBundle, Red::CName aName)
{
    if (!aName.hash)
    {
        return nullptr;
    }
    auto* found = aBundle->definitionsByName.Get(aName);
    return found && *found ? reinterpret_cast<Red::ScriptClass*>(*found) : nullptr;
}

std::mutex g_missingLock;
std::set<std::string> g_missingParents;

struct PortCounts
{
    uint32_t nativeDefs = 0;
    uint32_t structsFlagged = 0;
    uint32_t iserializable = 0;
    uint32_t audioLod = 0;
    uint32_t derived = 0;
    uint32_t parentsSet = 0;
    uint32_t abstractCopied = 0;
    uint32_t abstractChanged = 0;
    uint32_t parentMissing = 0;
    uint32_t aliasUsed = 0;
    uint32_t noNativeClass = 0;
    int gameuiBaseUIData = -1;
    int scnChatter = -1;
};

// Port of ScriptingService::OnValidateScripts with the layout guard and null checks.
void PreValidate(Red::ScriptBundle* aBundle)
{
    // Game 2.5: the shared script names are bound to Codeware's types before the scripts are checked (as on Windows).
    App::VanillaApiCompat::Apply();

    const auto layout = CheckLayout(aBundle);
    if (!layout.ok)
    {
        MAC_DIAG( "[cw] R15 validator layout check failed: %s\n", layout.which.c_str());
        return;
    }
    MAC_DIAG( "[cw] R15 validator layout ok classes=%u\n", layout.classCount);

    PortCounts c;

    auto* rtti = Red::CRTTISystem::Get();
    auto* serializableNative = Red::GetClass(kISerializable);
    if (serializableNative)
    {
        if (auto* cls = Red::GetClass(kGameuiBaseUIData))
        {
            cls->parent = serializableNative;
            c.gameuiBaseUIData = 1;
        }
        else
        {
            c.gameuiBaseUIData = 0;
        }
        if (auto* cls = Red::GetClass(kScnChatter))
        {
            cls->parent = serializableNative;
            c.scnChatter = 1;
        }
        else
        {
            c.scnChatter = 0;
        }
    }

    auto* serializableDef = FindClassDef(aBundle, kISerializable);

    for (uint32_t i = 0; i < aBundle->classes.Size(); ++i)
    {
        auto* classDef = aBundle->classes[i];
        if (!classDef || !classDef->flags.isNative)
        {
            continue;
        }
        ++c.nativeDefs;

        // Game 2.5: the vanilla bundle declares ScriptableService / CallbackSystemEvent without `abstract`, but their script
        // names now resolve to Codeware's abstract types (VanillaApiCompat).
        if (App::VanillaApiCompat::IsSharedScriptName(classDef->name))
        {
            if (auto* sharedNative = Red::GetScriptClass(classDef->name))
            {
                classDef->flags.isAbstract = sharedNative->flags.isAbstract;
            }
        }

        if (classDef->name == kISerializable)
        {
            classDef->flags.isStruct = true;
            classDef->parent = nullptr;
            ++c.structsFlagged;
            ++c.iserializable;
        }
        else if (classDef->name == kAudioEventElement || classDef->name == kEntLODDefinition)
        {
            classDef->flags.isStruct = true;
            if (serializableDef)
            {
                classDef->parent = serializableDef;
            }
            ++c.structsFlagged;
            ++c.audioLod;
        }
        else if (!classDef->flags.isStruct)
        {
            auto* parentDef = classDef->parent;
            for (uint32_t depth = 0; parentDef && depth < 256; ++depth)
            {
                if (parentDef->name == kIScriptable)
                {
                    break;
                }
                if (parentDef->name == kISerializable)
                {
                    classDef->flags.isStruct = true;
                    ++c.structsFlagged;
                    ++c.derived;
                    break;
                }
                parentDef = parentDef->parent;
            }
        }

        if (classDef->flags.isStruct && classDef->name != kInkWidgetLibraryResource)
        {
            auto* nativeClass = Red::GetScriptClass(classDef->name);
            if (!nativeClass)
            {
                ++c.noNativeClass;
                continue;
            }

            const bool abstractBefore = classDef->flags.isAbstract;
            classDef->flags.isAbstract = nativeClass->flags.isAbstract;
            ++c.abstractCopied;
            if (abstractBefore != classDef->flags.isAbstract)
            {
                ++c.abstractChanged;
            }

            if (!classDef->parent && nativeClass->parent)
            {
                const auto nativeParentName = nativeClass->parent->name;
                auto* parentDef = FindClassDef(aBundle, nativeParentName);

                if (!parentDef && rtti)
                {
                    // ConvertNativeToScriptName is IRTTISystem vtable +0x118, next to +0x120
                    // (ConvertScriptToNativeName) that the game's CompareType calls. It returns the name it is
                    // given when there is no alias.
                    const auto alias = rtti->ConvertNativeToScriptName(nativeParentName);
                    if (alias.hash && alias != nativeParentName)
                    {
                        parentDef = FindClassDef(aBundle, alias);
                        if (parentDef)
                        {
                            ++c.aliasUsed;
                        }
                    }
                }

                if (parentDef)
                {
                    classDef->parent = parentDef;
                    ++c.parentsSet;
                }
                else
                {
                    ++c.parentMissing;
                    const std::string key =
                        std::string(NameStr(classDef->name)) + " -> " + NameStr(nativeParentName);
                    bool first = false;
                    {
                        std::lock_guard guard(g_missingLock);
                        first = g_missingParents.insert(key).second;
                    }
                    if (first)
                    {
                        MAC_DIAG(
                                     "[cw] R15 parent declaration missing in the bundle: class=%s parent=%s "
                                     "(parent left unset)\n",
                                     NameStr(classDef->name), NameStr(nativeParentName));
                    }
                }
            }
        }
    }

    MAC_DIAG(
                 "[cw] R15 Validate port classes=%u native=%u structsFlagged=%u (ISerializable=%u audioLod=%u "
                 "derived=%u) parentsSet=%u abstractCopied=%u (changed %u) parentMissing=%u aliasUsed=%u "
                 "noNativeClass=%u gameuiBaseUIData=%d scnChatter=%d\n",
                 layout.classCount, c.nativeDefs, c.structsFlagged, c.iserializable, c.audioLod, c.derived,
                 c.parentsSet, c.abstractCopied, c.abstractChanged, c.parentMissing, c.aliasUsed, c.noNativeClass,
                 c.gameuiBaseUIData, c.scnChatter);
}

void LogValidateSummary(bool aResult)
{
    MAC_DIAG(
                 "[cw] R15 Validate result=%d propertyChecks=%llu arrayChecks=%llu overrides: array=%llu "
                 "(regress kept %llu) bitfield=%llu wrapper=%llu curve=%llu enumMismatch=%llu\n",
                 aResult ? 1 : 0, static_cast<unsigned long long>(g_stats.propCalls.load()),
                 static_cast<unsigned long long>(g_stats.arrayCalls.load()),
                 static_cast<unsigned long long>(g_stats.arrayOverride.load()),
                 static_cast<unsigned long long>(g_stats.arrayRegress.load()),
                 static_cast<unsigned long long>(g_stats.bitfieldOverride.load()),
                 static_cast<unsigned long long>(g_stats.wrapperOverride.load()),
                 static_cast<unsigned long long>(g_stats.curveOverride.load()),
                 static_cast<unsigned long long>(g_stats.enumMismatch.load()));

    std::lock_guard guard(g_statsLock);
    for (const auto& [key, count] : g_bitfieldNative)
    {
        MAC_DIAG( "[cw] R15 bitfield rule type: %s (x%u)\n", key.c_str(), count);
    }
    for (const auto& [key, count] : g_enumNative)
    {
        MAC_DIAG( "[cw] R15 ENUM mismatch (not overridden): %s (x%u)\n", key.c_str(), count);
    }
}


void ResetStats()
{
    g_stats.propCalls = 0;
    g_stats.arrayCalls = 0;
    g_stats.arrayOverride = 0;
    g_stats.arrayRegress = 0;
    g_stats.bitfieldOverride = 0;
    g_stats.wrapperOverride = 0;
    g_stats.curveOverride = 0;
    g_stats.enumMismatch = 0;
    g_stats.stillRejected = 0;
    g_stats.loggedArray = 0;
    g_stats.loggedBitfield = 0;
    g_stats.loggedWrapper = 0;
    g_stats.loggedCurve = 0;
    g_stats.loggedEnum = 0;
    std::lock_guard guard(g_statsLock);
    g_bitfieldNative.clear();
    g_enumNative.clear();
}

bool ShouldLog(std::atomic<uint32_t>& aCounter, uint32_t aLimit)
{
    return aCounter.fetch_add(1, std::memory_order_relaxed) < aLimit;
}

// Full hook on ScriptValidator::Validate. The Windows code runs OnValidateScripts before the original (HookBefore).
// This does the same and then logs the counts.
bool OnValidate(void* aValidator, Red::ScriptBundle* aBundle, void* aReport)
{
    g_stats.validateCalls.fetch_add(1, std::memory_order_relaxed);
    ResetStats();

    try
    {
        PreValidate(aBundle);
    }
    catch (...)
    {
        MAC_DIAG( "[cw] R15 Validate port exception (original runs unchanged)\n");
    }

    const bool result = Raw::ScriptValidator::Validate(aValidator, aBundle, aReport);
    // The bundle's ScriptProperty objects are freed with the bundle; a crash report after this point must not read them.
    g_lastScriptProp.store(nullptr, std::memory_order_relaxed);
    g_lastNativeProp.store(nullptr, std::memory_order_relaxed);
    Mac::MarkScriptsValidated(); // R18. The ScriptBundle destructor hook starts the services only after this.

    try
    {
        LogValidateSummary(result);
    }
    catch (...)
    {
    }
    return result;
}

// Full hook on ScriptValidator::ValidateProperty. Port of ScriptingService::OnValidateProperty with the
// CompareTypeName rules folded in (CompareTypeName is inlined on Mac and cannot be hooked).
bool OnValidateProperty(void* aValidator, Red::ScriptProperty* aScriptProp, Red::CProperty* aNativeProp)
{
    g_stats.propCalls.fetch_add(1, std::memory_order_relaxed);
    g_lastScriptProp.store(aScriptProp, std::memory_order_relaxed);
    g_lastNativeProp.store(aNativeProp, std::memory_order_relaxed);

    if (!aNativeProp || !aNativeProp->type)
    {
        // R17 guard. A native property that is missing, or has no type (its type name did not resolve when the class was
        // described), makes the game fault: ValidateProperty reads the type, and so does the report the game writes for a
        // rejected property (a plain "return false" was tried and faulted in that report, see the C1 boots). So the
        // property is rejected with a stand-in type, "Bool", set on the native property before the report runs: the
        // class fails to link, the LINKERR decode names it, and nothing dereferences null. The stand-in only exists
        // on a property that is already broken.
        static std::atomic<uint32_t> s_logged{0};
        if (s_logged.fetch_add(1) < 40)
        {
            char who[256];
            if (aScriptProp)
            {
                PropNames(aScriptProp, who, sizeof(who));
            }
            else
            {
                std::snprintf(who, sizeof(who), "<unknown>");
            }
            std::fprintf(stderr, "[cw] validator: native property %s has no type (script type %s)\n", who,
                         (aScriptProp && aScriptProp->type) ? NameStr(aScriptProp->type->name) : "?");
        }
        g_stats.stillRejected.fetch_add(1, std::memory_order_relaxed);
        if (aNativeProp)
        {
            if (auto* rtti = RED4ext::CRTTISystem::Get())
            {
                if (auto* standIn = rtti->GetType(RED4ext::CName("Bool")))
                {
                    aNativeProp->type = standIn;
                }
            }
        }
        return false;
    }

    if (!aScriptProp || !aNativeProp || !aScriptProp->type || !aNativeProp->type)
    {
        return Raw::ScriptValidator::ValidateProperty(aValidator, aScriptProp, aNativeProp);
    }

    auto* scriptType = aScriptProp->type;
    auto* nativeType = aNativeProp->type;
    const auto meta = scriptType->metaType;

    if (meta == Red::EScriptType::DynArray || meta == Red::EScriptType::StaticArray)
    {
        g_stats.arrayCalls.fetch_add(1, std::memory_order_relaxed);

        NameRule rule = NameRule::None;
        const bool mine = ValidateScriptType(nativeType, scriptType, rule);
        const bool orig = Raw::ScriptValidator::ValidateProperty(aValidator, aScriptProp, aNativeProp);

        if (mine && !orig)
        {
            g_stats.arrayOverride.fetch_add(1, std::memory_order_relaxed);
            if (ShouldLog(g_stats.loggedArray, 3))
            {
                char who[256];
                PropNames(aScriptProp, who, sizeof(who));
                MAC_DIAG( "[cw] R15 override array %s script=%s native=%s via=%s\n", who,
                             NameStr(scriptType->name), NameStr(nativeType->GetName()),
                             rule == NameRule::None ? "recursion" : (rule != NameRule::Curve ? "wrapper" : "curve"));
            }
        }
        else if (!mine && orig)
        {
            g_stats.arrayRegress.fetch_add(1, std::memory_order_relaxed);
            return true;
        }
        else if (!mine)
        {
            g_stats.stillRejected.fetch_add(1, std::memory_order_relaxed);
        }
        return mine;
    }

    if (nativeType->GetType() == Red::ERTTIType::BitField && meta == Red::EScriptType::Primitive)
    {
        const bool orig = Raw::ScriptValidator::ValidateProperty(aValidator, aScriptProp, aNativeProp);
        if (!orig)
        {
            g_stats.bitfieldOverride.fetch_add(1, std::memory_order_relaxed);
            {
                const std::string key =
                    std::string(NameStr(scriptType->name)) + " vs " + NameStr(nativeType->GetName()) + " [BitField]";
                std::lock_guard guard(g_statsLock);
                ++g_bitfieldNative[key];
            }
            if (ShouldLog(g_stats.loggedBitfield, 3))
            {
                char who[256];
                PropNames(aScriptProp, who, sizeof(who));
                MAC_DIAG( "[cw] R15 override bitfield %s script=%s native=%s\n", who,
                             NameStr(scriptType->name), NameStr(nativeType->GetName()));
            }
        }
        return true;
    }

    if (Raw::ScriptValidator::ValidateProperty(aValidator, aScriptProp, aNativeProp))
    {
        return true;
    }

    if (meta == Red::EScriptType::Primitive || meta == Red::EScriptType::Class)
    {
        Red::CName matched;
        const auto rule = MatchScriptType(scriptType, nativeType, &matched);
        if (rule != NameRule::None)
        {
            auto& counter = rule != NameRule::Curve ? g_stats.wrapperOverride : g_stats.curveOverride;
            auto& logged = rule != NameRule::Curve ? g_stats.loggedWrapper : g_stats.loggedCurve;
            counter.fetch_add(1, std::memory_order_relaxed);
            if (ShouldLog(logged, 3))
            {
                char who[256];
                PropNames(aScriptProp, who, sizeof(who));
                MAC_DIAG( "[cw] R15 override %s %s script=%s native=%s\n",
                             rule != NameRule::Curve ? "wrapper" : "curve", who, NameStr(matched),
                             NameStr(nativeType->GetName()));
            }
            return true;
        }
    }

    if (meta == Red::EScriptType::Primitive && nativeType->GetType() == Red::ERTTIType::Enum)
    {
        g_stats.enumMismatch.fetch_add(1, std::memory_order_relaxed);
        {
            const std::string key =
                std::string(NameStr(scriptType->name)) + " vs " + NameStr(nativeType->GetName()) + " [Enum]";
            std::lock_guard guard(g_statsLock);
            ++g_enumNative[key];
        }
        if (ShouldLog(g_stats.loggedEnum, 40))
        {
            char who[256];
            PropNames(aScriptProp, who, sizeof(who));
            MAC_DIAG( "[cw] R15 enum mismatch (not overridden) %s script=%s native=%s\n", who,
                         NameStr(scriptType->name), NameStr(nativeType->GetName()));
        }
    }

    g_stats.stillRejected.fetch_add(1, std::memory_order_relaxed);
    return false;
}

class ScriptValidatorHooks : public Core::HookingAgent
{
public:
    static bool Install()
    {
        const bool validateOk =
            IsHooked<Raw::ScriptValidator::Validate>() || Hook<Raw::ScriptValidator::Validate>(&OnValidate);
        MAC_DIAG_UNLESS(validateOk, "[cw] hook %s ScriptValidator::Validate target=%p\n", validateOk ? "installed" : "FAILED",
                     reinterpret_cast<void*>(Raw::ScriptValidator::Validate.GetOriginalAddress()));

        const bool propertyOk = IsHooked<Raw::ScriptValidator::ValidateProperty>() ||
                                Hook<Raw::ScriptValidator::ValidateProperty>(&OnValidateProperty);
        MAC_DIAG_UNLESS(propertyOk, "[cw] hook %s ScriptValidator::ValidateProperty target=%p\n",
                     propertyOk ? "installed" : "FAILED",
                     reinterpret_cast<void*>(Raw::ScriptValidator::ValidateProperty.GetOriginalAddress()));

        MAC_DIAG( "[cw] R15 CompareType (plain call) at %p\n",
                     reinterpret_cast<void*>(Raw::ScriptValidator::CompareType.GetOriginalAddress()));
        return validateOk && propertyOk;
    }
};

// ---- opcode handlers. Bodies of ScriptingService::ScriptOpCodeNew and ScriptOpCodeCast. The code stream is not
// aligned, so the operands are read with memcpy. CStackFrame::code is at +0x00 (the game's dispatcher loads the
// opcode through [frame] and advances it, 0x943974).
std::atomic<uint32_t> g_newCalls{0};
std::atomic<uint32_t> g_castCalls{0};

void ScriptOpCodeNew(Red::IScriptable*, Red::CStackFrame* aFrame, void* aRet, Red::CBaseRTTIType*)
{
    Red::CClass* instanceType = nullptr;
    std::memcpy(&instanceType, aFrame->code, sizeof(instanceType));
    aFrame->code += sizeof(Red::CClass*);

    if (g_newCalls.fetch_add(1, std::memory_order_relaxed) < 3)
    {
        MAC_DIAG( "[cw] R15 opcode New class=%s ret=%p\n",
                     instanceType ? NameStr(instanceType->GetName()) : "<null>", aRet);
    }

    if (aRet && instanceType)
    {
        *reinterpret_cast<Red::Handle<Red::ISerializable>*>(aRet) = Red::MakeScriptedHandle(instanceType);
    }
}

void ScriptOpCodeCast(Red::IScriptable*, Red::CStackFrame* aFrame, void* aLhs, Red::CBaseRTTIType*)
{
    Red::CClass* lhsType = nullptr;
    std::memcpy(&lhsType, aFrame->code, sizeof(lhsType));
    aFrame->code += sizeof(Red::CClass*);

    bool isWeak = false;
    std::memcpy(&isWeak, aFrame->code, sizeof(isWeak));
    aFrame->code += sizeof(bool);

    if (g_castCalls.fetch_add(1, std::memory_order_relaxed) < 3)
    {
        MAC_DIAG( "[cw] R15 opcode Cast class=%s weak=%d out=%p\n",
                     lhsType ? NameStr(lhsType->GetName()) : "<null>", isWeak ? 1 : 0, aLhs);
    }

    if (isWeak)
    {
        Red::WeakHandle<Red::ISerializable> rhsWeak;
        Red::GetParameter(aFrame, &rhsWeak);

        if (aLhs)
        {
            auto rhs = rhsWeak.Lock();
            if (rhs && lhsType && !rhs->GetType()->IsA(lhsType))
            {
                rhs.Reset();
            }

            *reinterpret_cast<Red::WeakHandle<Red::ISerializable>*>(aLhs) = rhs;
        }
    }
    else
    {
        Red::Handle<Red::ISerializable> rhs;
        Red::GetParameter(aFrame, &rhs);

        if (aLhs)
        {
            if (rhs && lhsType && !rhs->GetType()->IsA(lhsType))
            {
                rhs.Reset();
            }

            *reinterpret_cast<Red::Handle<Red::ISerializable>*>(aLhs) = rhs;
        }
    }
}

// Makes the page of the table entries writable when it is not, and restores the protection afterwards.
struct TableWriteAccess
{
    explicit TableWriteAccess(void* aAddress, size_t aSize)
    {
        const auto pageSize = static_cast<uintptr_t>(getpagesize());
        m_start = reinterpret_cast<uintptr_t>(aAddress) & ~(pageSize - 1);
        m_size = ((reinterpret_cast<uintptr_t>(aAddress) + aSize + pageSize - 1) & ~(pageSize - 1)) - m_start;

        vm_address_t region = static_cast<vm_address_t>(m_start);
        vm_size_t regionSize = 0;
        vm_region_basic_info_data_64_t info{};
        mach_msg_type_number_t count = VM_REGION_BASIC_INFO_COUNT_64;
        mach_port_t object = MACH_PORT_NULL;
        if (vm_region_64(mach_task_self(), &region, &regionSize, VM_REGION_BASIC_INFO_64,
                         reinterpret_cast<vm_region_info_t>(&info), &count, &object) != KERN_SUCCESS ||
            region > m_start)
        {
            m_ok = false;
            return;
        }

        m_oldProtection = info.protection;
        m_writable = (info.protection & VM_PROT_WRITE) != 0;
        if (m_writable)
        {
            m_ok = true;
            return;
        }

        m_ok = vm_protect(mach_task_self(), static_cast<vm_address_t>(m_start), static_cast<vm_size_t>(m_size), FALSE,
                          VM_PROT_READ | VM_PROT_WRITE | VM_PROT_COPY) == KERN_SUCCESS;
        m_changed = m_ok;
    }

    ~TableWriteAccess()
    {
        if (m_changed)
        {
            vm_protect(mach_task_self(), static_cast<vm_address_t>(m_start), static_cast<vm_size_t>(m_size), FALSE,
                       m_oldProtection);
        }
    }

    bool Ok() const
    {
        return m_ok;
    }

    bool Changed() const
    {
        return m_changed;
    }

private:
    uintptr_t m_start = 0;
    size_t m_size = 0;
    vm_prot_t m_oldProtection = 0;
    bool m_ok = false;
    bool m_writable = false;
    bool m_changed = false;
};
}

bool Mac::InstallScriptValidatorHooks()
{
    return ScriptValidatorHooks::Install();
}

void Mac::PatchScriptOpCodes(const char* aStage)
{
    const bool atLoad = aStage && std::strcmp(aStage, "load") == 0;
    const uintptr_t base = Red::MacGameBase();
    auto* table = reinterpret_cast<uintptr_t*>(base + kOpcodeTableRva);

    const auto oursNew = reinterpret_cast<uintptr_t>(&ScriptOpCodeNew);
    const auto oursCast = reinterpret_cast<uintptr_t>(&ScriptOpCodeCast);

    uintptr_t curNew = 0;
    uintptr_t curCast = 0;
    if (!SafeRead(&table[kOpNew], curNew) || !SafeRead(&table[kOpCast], curCast))
    {
        MAC_DIAG( "[cw] R15 opcodes stage=%s: table at %p is not readable, nothing written\n",
                     aStage ? aStage : "?", static_cast<void*>(table));
        return;
    }

    auto rva = [base](uintptr_t aPtr) -> long { return aPtr ? static_cast<long>(aPtr - base) : 0; };
    MAC_DIAG( "[cw] R15 opcodes stage=%s table=0x%lx entry%u(New)=0x%lx entry%u(Cast)=0x%lx (RVA, 0 = null)\n",
                 aStage ? aStage : "?", static_cast<long>(kOpcodeTableRva), static_cast<unsigned>(kOpNew), rva(curNew),
                 static_cast<unsigned>(kOpCast), rva(curCast));

    if (curNew == oursNew && curCast == oursCast)
    {
        MAC_DIAG( "[cw] R15 opcodes already ours\n");
        return;
    }

    if (atLoad && (!curNew || !curCast))
    {
        MAC_DIAG( "[cw] R15 opcodes not set at load, will be written in codeware_postLoadScripts\n");
        return;
    }

    TableWriteAccess access(&table[kOpNew < kOpCast ? kOpNew : kOpCast], sizeof(uintptr_t) * (kOpCast + 1));
    if (!access.Ok())
    {
        MAC_DIAG( "[cw] R15 opcodes: the table page cannot be made writable, nothing written\n");
        return;
    }

    table[kOpNew] = oursNew;
    table[kOpCast] = oursCast;
    MAC_DIAG( "[cw] R15 opcodes New 0x%lx -> ours (%p), Cast 0x%lx -> ours (%p)%s\n", rva(curNew),
                 reinterpret_cast<void*>(oursNew), rva(curCast), reinterpret_cast<void*>(oursCast),
                 access.Changed() ? " (page protection changed and restored)" : "");
}

void Mac::DescribeLastValidatedProperty(char* aOut, unsigned long aSize)
{
    if (!aOut || aSize == 0)
    {
        return;
    }
    aOut[0] = '\0';
    auto* script = g_lastScriptProp.load(std::memory_order_relaxed);
    auto* native = g_lastNativeProp.load(std::memory_order_relaxed);
    if (!script)
    {
        return;
    }
    char who[256];
    PropNames(script, who, sizeof(who));
    std::snprintf(aOut, aSize, "%s script=%s native=%s", who,
                  script->type ? NameStr(script->type->name) : "<null type>",
                  (native && native->type) ? NameStr(native->type->GetName()) : "<null>");
}
