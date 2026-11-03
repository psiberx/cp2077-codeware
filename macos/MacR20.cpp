// SELFTEST R20. See MacR20.hpp.

#include "MacR20.hpp"

#include "MacDiag.hpp"
#include "MacEngine.hpp"

#include <RED4ext/RED4ext.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/CompoundWidget.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/WidgetLibraryItemInstance.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/WidgetLibraryResource.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/WidgetLogicController.hpp>
#include <RED4ext/Scripting/Natives/inkLayer.hpp>
#include <RED4ext/Scripting/Natives/inkWidget.hpp>

#include <atomic>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <set>
#include <string>

std::string cw_key_to_text(int aVirtualKey); // macos/KeyTranslate.mm

namespace
{
// CODEWARE_MAC_DUMP_REFLECTION=<file>: writes every native class and property of the running game (name, parent, size, property
// offset and type) as a TSV, for the offline comparison with the SDK headers (the R21 offset sweep). Off by default.
void DumpReflection(const char* aPath)
{
    auto* rtti = RED4ext::CRTTISystem::Get();
    if (!rtti)
        return;
    std::FILE* out = std::fopen(aPath, "w");
    if (!out)
    {
        MAC_DIAG( "[selftest] R20 reflection dump: cannot open %s\n", aPath);
        return;
    }
    RED4ext::DynArray<RED4ext::CClass*> classes;
    rtti->GetClasses(nullptr, classes);
    unsigned propCount = 0;
    for (auto* cls : classes)
    {
        if (!cls)
            continue;
        std::fprintf(out, "C\t%s\t%s\t%u\t%u\t%u\n", cls->name.ToString(), cls->parent ? cls->parent->name.ToString() : "",
                     cls->size, cls->holderSize, cls->alignment);
        for (uint32_t i = 0; i < cls->props.Size(); ++i)
        {
            auto* prop = cls->props[i];
            if (!prop)
                continue;
            ++propCount;
            std::fprintf(out, "P\t%s\t%s\t%u\t%s\n", cls->name.ToString(), prop->name.ToString(), prop->valueOffset,
                         prop->type ? prop->type->GetName().ToString() : "");
        }
    }
    std::fclose(out);
    MAC_DIAG( "[selftest] R20 reflection dump: %u classes, %u properties -> %s\n", static_cast<unsigned>(classes.Size()),
                 propCount, aPath);
}
}

namespace
{
// The offset of a member as the SDK header declares it (the layout the Windows reflection dump gave).
template<typename T, typename M>
uint32_t SdkOffset(M T::*aMember)
{
    alignas(16) static char storage[1024];
    auto* object = reinterpret_cast<T*>(storage);
    return static_cast<uint32_t>(reinterpret_cast<char*>(&(object->*aMember)) - storage);
}

struct OffsetCase
{
    const char* className;
    const char* propName;
    uint32_t sdkOffset;
    bool asserted = true; // false: logged only (unverified members, see the reflection sweep)
};

std::atomic<int> s_checks{0};
std::atomic<int> s_failed{0};
std::mutex s_onceMutex;
std::set<std::string> s_once;
}

void Mac::R20Check(bool aOk, const char* aWhat)
{
    s_checks.fetch_add(1);
    if (!aOk)
    {
        s_failed.fetch_add(1);
        MAC_DIAG( "[selftest] R20 FAIL %s\n", aWhat);
    }
}

void Mac::R20Summary(const char* aWhen)
{
    if (!Mac::DiagEnabled())
    {
        return;
    }
    const int failed = s_failed.load();
    MAC_DIAG( "[selftest] R20 %s@%s (checks=%d failed=%d)\n", failed == 0 ? "PASS" : "FAIL", aWhen, s_checks.load(),
                 failed);
}

bool Mac::R20Once(const char* aName)
{
    if (!Mac::DiagEnabled())
    {
        return false;
    }
    std::lock_guard<std::mutex> lock(s_onceMutex);
    return s_once.insert(aName).second;
}

void Mac::R20PostLoadScripts()
{
    if (const char* dump = std::getenv("CODEWARE_MAC_DUMP_REFLECTION"))
    {
        DumpReflection(dump);
    }

    if (!Mac::DiagEnabled())
    {
        return;
    }

    // The SDK structs the UI services read (inkWidget, inkCompoundWidget, inkLogicController, the library instance and resource,
    // inkLayer) against the game's own reflection on this build: the reflected property offset must equal the SDK member offset.
    // A mismatch means the Windows layout does not hold on Mac for that class.
    using namespace RED4ext;
    const OffsetCase cases[] = {
        {"inkWidget", "logicController", SdkOffset(&ink::Widget::logicController)},
        {"inkWidget", "parentWidget", SdkOffset(&ink::Widget::parentWidget)},
        {"inkWidget", "name", SdkOffset(&ink::Widget::name)},
        {"inkWidget", "size", SdkOffset(&ink::Widget::size)},
        {"inkWidget", "opacity", SdkOffset(&ink::Widget::opacity)},
        {"inkWidget", "visible", SdkOffset(&ink::Widget::visible)},
        {"inkCompoundWidget", "childOrder", SdkOffset(&ink::CompoundWidget::childOrder)},
        {"inkCompoundWidget", "children", SdkOffset(&ink::CompoundWidget::children)},
        {"inkWidgetLogicController", "widget", SdkOffset(&ink::WidgetLogicController::widget)},
        {"inkLayer", "window", SdkOffset(&ink::Layer::window), false},
        {"inkLayer", "libraryItem", SdkOffset(&ink::Layer::libraryItem), false},
        {"inkLayer", "controllerProcessor", SdkOffset(&ink::Layer::controllerProcessor), false},
        {"inkLayer", "isInteractive", SdkOffset(&ink::Layer::isInteractive), false},
        {"inkLayer", "inputContext", SdkOffset(&ink::Layer::inputContext), false},
        {"inkWidgetLibraryItemInstance", "rootWidget", SdkOffset(&ink::WidgetLibraryItemInstance::rootWidget)},
        {"inkWidgetLibraryItemInstance", "gameController", SdkOffset(&ink::WidgetLibraryItemInstance::gameController)},
    };
    // KNOWN SHIFT (found by r20a): inkWidgetLibraryResource.libraryItems is at 0x40 and externalLibraries at 0x50 in the game, the SDK
    // header says 0x48 and 0x58. The game (clang, Itanium layout) puts rootResolution in the tail padding of CResource (0x39) and
    // rootDefinitionIndex at 0x3C; the generated header pads to the Windows offsets (explicit unk41[3]). Codeware must reach the
    // two arrays through the reflected property (WidgetSpawningService::InjectDependency does). Logged here, not asserted.
    for (const char* prop : {"libraryItems", "externalLibraries"})
    {
        auto* type = CRTTISystem::Get()->GetClass(CName("inkWidgetLibraryResource"));
        auto* property = type ? type->GetProperty(CName(prop)) : nullptr;
        MAC_DIAG( "[selftest] R20 offsets: inkWidgetLibraryResource.%s game %#x (SDK header %#x, known shift)\n", prop,
                     property ? property->valueOffset : 0u,
                     std::strcmp(prop, "libraryItems") == 0 ? SdkOffset(&ink::WidgetLibraryResource::libraryItems)
                                                             : SdkOffset(&ink::WidgetLibraryResource::externalLibraries));
    }
    // The element type of externalLibraries (Ref<inkWidgetLibraryResource>) must have the size the SDK assumes, because
    // InjectDependency appends to the array through the SDK type.
    {
        auto* type = CRTTISystem::Get()->GetClass(CName("inkWidgetLibraryResource"));
        auto* property = type ? type->GetProperty(CName("externalLibraries")) : nullptr;
        const auto kind = property && property->type ? property->type->GetType() : ERTTIType::Name;
        if (kind == ERTTIType::Array)
        {
            auto* inner = static_cast<CRTTIBaseArrayType*>(property->type)->GetInnerType();
            const uint32_t gameSize = inner ? inner->GetSize() : 0;
            const uint32_t sdkSize = sizeof(Ref<ink::WidgetLibraryResource>);
            MAC_DIAG( "[selftest] R20 externalLibraries element: game %u bytes, SDK %u bytes\n", gameSize, sdkSize);
            Mac::R20Check(gameSize == sdkSize, "the Ref element of externalLibraries has the SDK size");
        }
        else
        {
            Mac::R20Check(false, "externalLibraries is a reflected array property");
        }
    }
    int compared = 0;
    int mismatched = 0;
    for (const auto& item : cases)
    {
        auto* type = CRTTISystem::Get()->GetClass(CName(item.className));
        auto* prop = type ? type->GetProperty(CName(item.propName)) : nullptr;
        if (!prop)
        {
            MAC_DIAG( "[selftest] R20 offsets: %s.%s is not reflected (SDK %#x), skipped\n", item.className, item.propName,
                         item.sdkOffset);
            continue;
        }
        ++compared;
        const bool same = prop->valueOffset == item.sdkOffset;
        if (!same && item.asserted)
            ++mismatched;
        MAC_DIAG( "[selftest] R20 offsets: %s.%s game %#x sdk %#x %s\n", item.className, item.propName, prop->valueOffset,
                     item.sdkOffset, same ? "ok" : "MISMATCH");
    }
    MAC_DIAG( "[selftest] R20 offsets: %d members compared, %d mismatched\n", compared, mismatched);
    Mac::R20Check(compared >= 1, "some UI struct members are reflected to compare");
    Mac::R20Check(mismatched == 0, "the SDK offsets of the UI structs equal the game's reflected offsets");

    // WidgetInputService::ToCharacter on macOS: EInputKey (Windows virtual-key codes) to the text of the active layout. No
    // shortcut modifier is held during a test boot, so a letter, a digit, the space bar and a punctuation key give text.
    const std::string a = cw_key_to_text(65);     // IK_A
    const std::string one = cw_key_to_text(49);   // IK_1
    const std::string space = cw_key_to_text(32); // IK_Space
    const std::string equals = cw_key_to_text(187);
    const std::string none = cw_key_to_text(112); // IK_F1: not a character key
    MAC_DIAG( "[selftest] R20 key text: A=\"%s\" 1=\"%s\" space=\"%s\" equals=\"%s\" F1=\"%s\"\n", a.c_str(), one.c_str(),
                 space.c_str(), equals.c_str(), none.c_str());
    Mac::R20Check(a.size() == 1 && one.size() == 1, "a letter key and a digit key give one character");
    Mac::R20Check(space == " ", "the space bar gives a space");
    Mac::R20Check(!equals.empty() && none.empty(), "punctuation gives text and a non-character key gives none");
}

void Mac::R20CheckAtT50()
{
    if (!Mac::DiagEnabled())
    {
        return;
    }

    // Counters of the UI hooks (registered by the hooks; a hook that never ran reads 0).
    static const char* kNames[] = {
        "InkWidget_ScriptReparent",
        "InkCompoundWidget_ScriptAddChild",
        "InkLogicController_OnInitialize",
        "InkWidgetLibrary_SpawnFromLocal",
        "InkWidgetLibrary_SpawnFromExternal",
        "InkWidgetLibrary_AsyncSpawnFromLocal",
        "InkWidgetLibrary_AsyncSpawnFromExternal",
        "InkSpawner_FinishAsyncSpawn",
        "InkSystem_ProcessCharacterEvent",
        "InkWidget_TriggerEvent",
        "WidgetBuilding_AttachWidgetTree",
    };
    std::string line;
    for (const char* name : kNames)
    {
        char buf[96];
        std::snprintf(buf, sizeof(buf), " %s=%llu", name, static_cast<unsigned long long>(Mac::HookCount(name).calls.load()));
        line += buf;
    }
    MAC_DIAG( "[selftest] R20 UI counters@t+50s%s\n", line.c_str());

    // The widget layer lookup (WidgetBuildingService::OnInitializeController): of the widgets tried, at least one has a layer.
    const auto tries = Mac::HookCount("R20_GetLayer_tries").calls.load();
    const auto found = Mac::HookCount("R20_GetLayer_found").calls.load();
    MAC_DIAG( "[selftest] R20 GetLayer: tried %llu widgets with a parent, %llu had a layer\n",
                 static_cast<unsigned long long>(tries), static_cast<unsigned long long>(found));
    Mac::R20Check(tries > 0 && found > 0, "GetLayer finds the inkLayer of a menu widget");
    // The UI hooks ran in the real menu: controllers initialized and library items spawned.
    Mac::R20Check(Mac::HookCount("InkLogicController_OnInitialize").calls.load() > 0, "the OnInitialize hook saw controllers");
    Mac::R20Check(Mac::HookCount("InkWidgetLibrary_SpawnFromLocal").calls.load() > 0, "the SpawnFromLocal hook saw library spawns");
}
