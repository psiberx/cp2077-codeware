// Mac support for the Codeware dylib. Vault, vslot, and value-holder copies
// of TweakXL's MacRegisterNatives.cpp. Symbols stay hidden so each dylib
// binds its own copy. Id ranges are disjoint from TweakXL.

#include "MacDiag.hpp"
#include "Red/TypeInfo.hpp"

#include "MacAddressResolver.hpp"

#include <RED4ext/Hashing/FNV1a.hpp>
#include <RED4ext/Memory/Vault.hpp>

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <dlfcn.h>
#include <mach/mach.h>
#include <mach-o/dyld.h>
#include <mach-o/loader.h>

// Local stand-in. Codeware starts below TweakXL's 0x7FFF0000 range.
extern "C" __attribute__((visibility("hidden"))) uint32_t tweakxl_rtti_async_id = 0x7FFE0000;

// Local stand-in. Codeware's ids sit one band above TweakXL's 1<<62 range.
extern "C" __attribute__((visibility("hidden"))) volatile int64_t tweakxl_serializable_counter =
    (1LL << 62) + (1LL << 61);

namespace
{
// Exported PoolStorageProxy functions. Static. Block comes back in x0/x1.
// dlsym wants one leading underscore. dyld_info prints two.
constexpr uint64_t kTagRtti = 0x10;
constexpr uint64_t kTagFunction = 0x20;
constexpr uint64_t kTagProperty = 0x30;
// R14. Scripted classes live in PoolScript. A C++ Handle to a scripted instance (a ScriptableTweak or a
// ScriptableService subclass written in redscript) frees it through Allocator<PoolScript>, which looks the pool up
// in this vault. Without the entry the lookup returns null and the free faults at +0x10.
constexpr uint64_t kTagScript = 0x40;

struct GameBlock
{
    void* memory;
    uint64_t size;
};

struct PoolOps
{
    const char* name;
    uint64_t tag;
    uintptr_t expect[5];
    GameBlock (*alloc)(uint64_t);
    GameBlock (*allocAligned)(uint64_t, uint32_t);
    GameBlock (*realloc)(GameBlock&, uint64_t);
    GameBlock (*reallocAligned)(GameBlock&, uint64_t, uint32_t);
    void (*freeFn)(GameBlock&);
};

PoolOps g_pools[] = {
    {"8PoolRTTI", kTagRtti, {0x10A1FA4, 0x10A20C0, 0x10A21EC, 0x10A2324, 0x10A2408}, nullptr, nullptr, nullptr, nullptr, nullptr},
    {"16PoolRTTIFunction", kTagFunction, {0x10A268C, 0x10a27a8, 0x10A28D4, 0x10A2A0C, 0x10A2AF0}, nullptr, nullptr, nullptr, nullptr, nullptr},
    {"16PoolRTTIProperty", kTagProperty, {0x10A2D74, 0x10A2E90, 0x10A2FBC, 0x10A30F4, 0x10A31D8}, nullptr, nullptr, nullptr, nullptr, nullptr},
    // R14. Exports checked with nm: Allocate 0x344DCAC, AllocateAligned 0x344DDD0, Reallocate 0x344DF10,
    // ReallocateAligned 0x344E05C, Free 0x344E144.
    {"10PoolScript", kTagScript, {0x4E33A00, 0x4E33B1C, 0x4E33C48, 0x4E33D80, 0x4E33E64}, nullptr, nullptr, nullptr, nullptr, nullptr},
};

const char* kPoolSuffixes[5] = {
    "8AllocateEy",
    "15AllocateAlignedEyj",
    "10ReallocateERNS0_5BlockEy",
    "17ReallocateAlignedERNS0_5BlockEyj",
    "4FreeERNS0_5BlockE",
};

bool g_vaultSymbolsOk = false;

RED4ext::Memory::Vault g_vault;
RED4ext::Memory::PoolStorage g_rttiStorage;
RED4ext::Memory::PoolStorage g_functionStorage;
RED4ext::Memory::PoolStorage g_propertyStorage;
RED4ext::Memory::PoolStorage g_scriptStorage; // R14
bool g_vaultReady = false;

uintptr_t GameBase()
{
    const uint32_t count = _dyld_image_count();
    for (uint32_t i = 0; i < count; ++i)
    {
        const auto* header = reinterpret_cast<const mach_header_64*>(_dyld_get_image_header(i));
        if (header && header->filetype == MH_EXECUTE)
        {
            return reinterpret_cast<uintptr_t>(header);
        }
    }
    return reinterpret_cast<uintptr_t>(_dyld_get_image_header(0));
}

void FillPool(uint32_t aIndex, const char* aName, RED4ext::Memory::PoolStorage& aStorage, uint64_t aTag)
{
    auto& node = g_vault.poolRegistry.nodes[aIndex];
    std::memset(&node, 0, sizeof(node));
    node.handle = RED4ext::FNV1a32(aName);
    node.storage = &aStorage;
    aStorage.allocatorStorage = aTag;
    std::strncpy(node.name, aName, sizeof(node.name) - 1);
}

bool AddressInImage(uint32_t aIndex, uintptr_t aAddr)
{
    const auto* header = reinterpret_cast<const mach_header_64*>(_dyld_get_image_header(aIndex));
    if (!header)
    {
        return false;
    }
    const intptr_t slide = _dyld_get_image_vmaddr_slide(aIndex);
    auto* cmd = reinterpret_cast<const load_command*>(header + 1);
    for (uint32_t i = 0; i < header->ncmds; ++i)
    {
        if (cmd->cmd == LC_SEGMENT_64)
        {
            const auto* seg = reinterpret_cast<const segment_command_64*>(cmd);
            const auto start = static_cast<uintptr_t>(seg->vmaddr) + static_cast<uintptr_t>(slide);
            const auto end = start + seg->vmsize;
            if (aAddr >= start && aAddr < end)
            {
                return true;
            }
        }
        cmd = reinterpret_cast<const load_command*>(reinterpret_cast<const uint8_t*>(cmd) + cmd->cmdsize);
    }
    return false;
}

int ImageIndex(const char* aNamePart, uint32_t aFileType)
{
    const uint32_t count = _dyld_image_count();
    for (uint32_t i = 0; i < count; ++i)
    {
        const auto* header = reinterpret_cast<const mach_header_64*>(_dyld_get_image_header(i));
        const char* name = _dyld_get_image_name(i);
        if (!header)
        {
            continue;
        }
        if (aFileType != 0 && header->filetype != aFileType)
        {
            continue;
        }
        if (aNamePart && (!name || !std::strstr(name, aNamePart)))
        {
            continue;
        }
        return static_cast<int>(i);
    }
    return -1;
}

void InitVault()
{
    if (g_vaultReady)
    {
        return;
    }
    std::memset(&g_vault, 0, sizeof(g_vault));
    std::memset(&g_rttiStorage, 0, sizeof(g_rttiStorage));
    std::memset(&g_functionStorage, 0, sizeof(g_functionStorage));
    std::memset(&g_propertyStorage, 0, sizeof(g_propertyStorage));
    std::memset(&g_scriptStorage, 0, sizeof(g_scriptStorage)); // R14
    FillPool(0, "PoolRTTI", g_rttiStorage, kTagRtti);
    FillPool(1, "PoolRTTIFunction", g_functionStorage, kTagFunction);
    FillPool(2, "PoolRTTIProperty", g_propertyStorage, kTagProperty);
    FillPool(3, "PoolScript", g_scriptStorage, kTagScript); // R14

    const uintptr_t base = GameBase();
    g_vaultSymbolsOk = true;
    for (auto& pool : g_pools)
    {
        void* slots[5] = {};
        for (int i = 0; i < 5; ++i)
        {
            char symbol[160];
            std::snprintf(symbol, sizeof(symbol), "_ZN3red6memory16PoolStorageProxyINS_%sEE%s", pool.name, kPoolSuffixes[i]);
            void* found = dlsym(RTLD_MAIN_ONLY, symbol);
            const auto addr = reinterpret_cast<uintptr_t>(found);
            const auto rva = found ? addr - base : 0;
            MAC_DIAG( "[vault] %s %s rva=%llx expected=%llx\n", pool.name, kPoolSuffixes[i],
                         static_cast<unsigned long long>(rva), static_cast<unsigned long long>(pool.expect[i]));
            if (!found || rva != pool.expect[i])
            {
                std::fprintf(stderr, "[vault] MISMATCH %s %s\n", pool.name, kPoolSuffixes[i]);
                g_vaultSymbolsOk = false;
                slots[i] = nullptr;
            }
            else
            {
                slots[i] = found;
            }
        }
        pool.alloc = reinterpret_cast<GameBlock (*)(uint64_t)>(slots[0]);
        pool.allocAligned = reinterpret_cast<GameBlock (*)(uint64_t, uint32_t)>(slots[1]);
        pool.realloc = reinterpret_cast<GameBlock (*)(GameBlock&, uint64_t)>(slots[2]);
        pool.reallocAligned = reinterpret_cast<GameBlock (*)(GameBlock&, uint64_t, uint32_t)>(slots[3]);
        pool.freeFn = reinterpret_cast<void (*)(GameBlock&)>(slots[4]);
    }
    MAC_DIAG( "[vault] ok=%d\n", g_vaultSymbolsOk ? 1 : 0);
    g_vaultReady = true;
}

PoolOps* PoolFor(uintptr_t aTag)
{
    for (auto& pool : g_pools)
    {
        if (pool.tag == aTag)
        {
            return &pool;
        }
    }
    std::fprintf(stderr, "[vault] unknown tag 0x%llx\n", static_cast<unsigned long long>(aTag));
    return nullptr;
}
}

// R13. The resolver and the hooking driver need the same MH_EXECUTE base the vault code uses.
uintptr_t Red::MacGameBase()
{
    return GameBase();
}

extern "C" __attribute__((visibility("hidden"))) void* tweakxl_memory_vault()
{
    InitVault();
    return &g_vault;
}

extern "C" __attribute__((visibility("hidden"))) void tweakxl_vault_alloc(void* aStorage, void* aResult, uint64_t aSize)
{
    InitVault();
    auto* result = static_cast<RED4ext::Memory::AllocationResult*>(aResult);
    result->memory = nullptr;
    result->size = 0;
    auto* pool = PoolFor(reinterpret_cast<uintptr_t>(aStorage));
    if (!pool || !pool->alloc)
    {
        return;
    }
    const GameBlock block = pool->alloc(aSize);
    result->memory = block.memory;
    result->size = block.memory ? block.size : 0;
}

extern "C" __attribute__((visibility("hidden"))) void tweakxl_vault_alloc_aligned(void* aStorage, void* aResult, uint64_t aSize, uint32_t aAlign)
{
    InitVault();
    auto* result = static_cast<RED4ext::Memory::AllocationResult*>(aResult);
    result->memory = nullptr;
    result->size = 0;
    auto* pool = PoolFor(reinterpret_cast<uintptr_t>(aStorage));
    if (!pool || !pool->allocAligned)
    {
        return;
    }
    const GameBlock block = pool->allocAligned(aSize, aAlign);
    result->memory = block.memory;
    result->size = block.memory ? block.size : 0;
}

extern "C" __attribute__((visibility("hidden"))) void tweakxl_vault_realloc(void* aStorage, void* aResult, void* aInput, uint64_t aSize)
{
    InitVault();
    auto* result = static_cast<RED4ext::Memory::AllocationResult*>(aResult);
    result->memory = nullptr;
    result->size = 0;
    auto* pool = PoolFor(reinterpret_cast<uintptr_t>(aStorage));
    if (!pool || !pool->realloc || !aInput)
    {
        return;
    }
    const GameBlock block = pool->realloc(*static_cast<GameBlock*>(aInput), aSize);
    result->memory = block.memory;
    result->size = block.memory ? block.size : 0;
}

extern "C" __attribute__((visibility("hidden"))) void tweakxl_vault_realloc_aligned(void* aStorage, void* aResult, void* aInput, uint64_t aSize, uint32_t aAlign)
{
    InitVault();
    auto* result = static_cast<RED4ext::Memory::AllocationResult*>(aResult);
    result->memory = nullptr;
    result->size = 0;
    auto* pool = PoolFor(reinterpret_cast<uintptr_t>(aStorage));
    if (!pool || !pool->reallocAligned || !aInput)
    {
        return;
    }
    const GameBlock block = pool->reallocAligned(*static_cast<GameBlock*>(aInput), aSize, aAlign);
    result->memory = block.memory;
    result->size = block.memory ? block.size : 0;
}

extern "C" __attribute__((visibility("hidden"))) void tweakxl_vault_free(void* aStorage, void* aInput)
{
    InitVault();
    auto* pool = PoolFor(reinterpret_cast<uintptr_t>(aStorage));
    if (!pool || !pool->freeFn || !aInput)
    {
        return;
    }
    pool->freeFn(*static_cast<GameBlock*>(aInput));
}

// R19: tweakxl_destruct_value_holder (the stand-in that logged "[vh] unexpected holder" and leaked the holder) is gone.
// IScriptable_DestructValueHolder resolves to the game function (0x22384BC) through MacSdkRows.inc.

extern "C" __attribute__((visibility("hidden"))) uintptr_t tweakxl_class_vslot(uint32_t aByteOffset)
{
    static bool ready = false;
    static uintptr_t slots[11] = {};
    static const uint32_t kOffsets[11] = {0x68, 0x70, 0x88, 0x90, 0x98, 0xA0, 0xA8, 0xB8, 0xC8, 0xD0, 0xD8};
    if (!ready)
    {
        auto* rtti = RED4ext::CRTTISystem::Get();
        auto* cls = rtti ? rtti->GetClass(RED4ext::CName("IScriptable")) : nullptr;
        if (!cls)
        {
            std::fprintf(stderr, "[vslot] IScriptable missing\n");
            return 0;
        }
        auto* vt = *reinterpret_cast<uintptr_t**>(cls);
        const uintptr_t base = GameBase();
        const int game = ImageIndex(nullptr, MH_EXECUTE);
        const int tweak = ImageIndex("TweakXL.dylib", 0);
        const int codeware = ImageIndex("Codeware.dylib", 0);
        MAC_DIAG( "[vslot] vtable=%p\n", static_cast<void*>(vt));
        for (int i = 0; i < 11; ++i)
        {
            const uintptr_t fn = vt[kOffsets[i] / 8];
            const bool inGame = game >= 0 && AddressInImage(static_cast<uint32_t>(game), fn);
            const bool inTweak = tweak >= 0 && AddressInImage(static_cast<uint32_t>(tweak), fn);
            const bool inCodeware = codeware >= 0 && AddressInImage(static_cast<uint32_t>(codeware), fn);
            MAC_DIAG( "[vslot] off=%x rva=%llx\n", kOffsets[i],
                         static_cast<unsigned long long>(fn - base));
            if (!inGame || inTweak || inCodeware)
            {
                std::fprintf(stderr, "[vslot] reject off=%x inGame=%d inTweakXL=%d inCodeware=%d\n", kOffsets[i],
                             inGame ? 1 : 0, inTweak ? 1 : 0, inCodeware ? 1 : 0);
                slots[i] = 0;
            }
            else
            {
                slots[i] = fn;
            }
        }
        ready = true;
    }
    for (int i = 0; i < 11; ++i)
    {
        if (kOffsets[i] == aByteOffset)
        {
            return slots[i];
        }
    }
    std::fprintf(stderr, "[vslot] unknown offset %x\n", aByteOffset);
    return 0;
}


#include "MacR13.hpp"
#include "MacR25.hpp"
#include "MacEngine.hpp"
#include "MacR19.hpp"
#include "MacR20.hpp"
#include "MacR15.hpp"

#include "Core/Hooking/HookingDriver.hpp"
#include "Support/macOS/Lifecycle.hpp"

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/MacHookStats.hpp"
#include "App/Environment.hpp"
#include "App/Facade.hpp"
#include "App/Scripting/ScriptableServiceContainer.hpp"
#include "App/Utils/String.hpp"
#include "Core/Facades/Runtime.hpp"
#include "Core/Runtime/HostImage.hpp"
#include "Core/Runtime/ModuleImage.hpp"

#include <RED4ext/Scripting/Natives/ScriptGameInstance.hpp>
#include <RED4ext/Scripting/OpcodeHandlers.hpp>

#include <cstring>
#include <exception>
#include <string>

namespace
{
bool g_logGameInstanceShape = false;

void LogPending(const char* aWhere)
{
    if (!Mac::DiagEnabled())
    {
        return;
    }
    MAC_DIAG( "[diag] pending %s register %zu describe %zu\n", aWhere,
                 Red::TypeInfoRegistrar::PendingRegisterCount(), Red::TypeInfoRegistrar::PendingDescribeCount());
}

RED4ext::CClass* FindClass(const char* aName, const char* aAlt, const char** aUsed)
{
    auto* rtti = RED4ext::CRTTISystem::Get();
    if (!rtti)
    {
        return nullptr;
    }
    auto* cls = rtti->GetClass(RED4ext::CName(aName));
    *aUsed = aName;
    if (!cls && aAlt)
    {
        cls = rtti->GetClass(RED4ext::CName(aAlt));
        if (cls)
        {
            *aUsed = aAlt;
        }
    }
    return cls;
}

void LogOneClass(const char* aName, const char* aAlt)
{
    const char* used = aName;
    auto* cls = FindClass(aName, aAlt, &used);
    if (cls)
    {
        MAC_DIAG( "[diag] %s found=1 abstract=%u funcs=%u staticFuncs=%u via=%s\n", aName,
                     static_cast<unsigned>(cls->flags.isAbstract), cls->funcs.Size(), cls->staticFuncs.Size(), used);
        return;
    }

    auto* rtti = RED4ext::CRTTISystem::Get();
    auto* type = rtti ? rtti->GetType(RED4ext::CName(aName)) : nullptr;
    const char* typeName = aName;
    if (!type && aAlt && rtti)
    {
        type = rtti->GetType(RED4ext::CName(aAlt));
        if (type)
        {
            typeName = aAlt;
        }
    }
    MAC_DIAG( "[diag] %s found=%d abstract=0 funcs=0 staticFuncs=0 via=%s kind=%s\n", aName, type ? 1 : 0,
                 typeName, type ? "type" : "missing");
}

void LogClasses()
{
    if (!Mac::DiagEnabled())
    {
        return;
    }
    struct Row
    {
        const char* name;
        const char* alt;
    };
    static const Row kRows[] = {
        {"CallbackSystem", nullptr},
        {"CallbackSystemEvent", nullptr},
        {"CallbackSystemHandler", nullptr},
        {"CallbackSystemTarget", nullptr},
        {"EntityLifecycleEvent", nullptr},
        {"ResourceEvent", nullptr},
        {"EntityTarget", nullptr},
        {"ResourceTarget", nullptr},
        {"WorldNodeSetupWrapper", nullptr},
        {"WorldStateSystem", nullptr},
        {"worldInstancedMeshNode", nullptr},
        {"worldStreamingSector", nullptr},
        {"CResource", nullptr},
        {"ResourceDepot", nullptr},
        {"ResourceRef", nullptr},
        {"ResourceAsyncRef", nullptr},
        {"inkCharacterEvent", nullptr},
        {"inkGrid", "inkGridWidget"},
        {"inkKeyInputEvent", nullptr},
        {"inkWidget", nullptr},
        {"inkWidgetRef", "inkWidgetReference"},
        {"inkSystem", nullptr},
        {"Reflection", nullptr},
        {"ReflectionClass", nullptr},
        {"ReflectionFunc", nullptr},
        {"ReflectionMemberFunc", nullptr},
        {"ReflectionType", nullptr},
        {"ISerializable", nullptr},
        {"ScriptableService", nullptr},
        {"ScriptableServiceContainer", nullptr},
        {"graphGraphSocketDefinition", nullptr},
        {"Entity", "entEntity"},
        {"Codeware", nullptr},
        {"WardrobeSystem", "gameWardrobeSystem"},
        {"JournalManager", "gameJournalManager"},
        {"ArchiveXL", nullptr},            // fallback stand-in class, skipped when the ArchiveXL plugin registers it (macos/ArchiveXLScripts.cpp)
        {"CodewareMacSelfTest", nullptr},  // SELFTEST R13 (macos/MacR13.cpp)
    };
    for (const auto& row : kRows)
    {
        LogOneClass(row.name, row.alt);
    }

    const char* gridUsed = "inkGrid";
    auto* grid = FindClass("inkGrid", "inkGridWidget", &gridUsed);
    bool orientation = false;
    if (grid)
    {
        const RED4ext::CName want("orientation");
        for (uint32_t i = 0; i < grid->props.Size(); ++i)
        {
            auto* prop = grid->props[i];
            if (prop && prop->name == want)
            {
                orientation = true;
                break;
            }
        }
    }
    MAC_DIAG( "[diag] inkGrid orientation=%d via=%s\n", orientation ? 1 : 0, gridUsed);
}

void LogGlobals()
{
    if (!Mac::DiagEnabled())
    {
        return;
    }
    auto* rtti = RED4ext::CRTTISystem::Get();
    for (const char* name : {"UTF8StrLower", "GameFileExists", "CreateNodeRef", "Murmur3", "Print"})
    {
        auto* fn = rtti ? rtti->GetFunction(RED4ext::CName(name)) : nullptr;
        MAC_DIAG( "[diag] global %s found=%d\n", name, fn ? 1 : 0);
    }
}

bool SystemInMap(const char* aName)
{
    auto* game = Red::MacGameInstance();
    auto* rtti = RED4ext::CRTTISystem::Get();
    auto* type = rtti ? rtti->GetClass(RED4ext::CName(aName)) : nullptr;
    if (!game || !type)
    {
        return false;
    }
    auto* slot = game->systemMap.Get(type);
    return slot && static_cast<bool>(*slot);
}

void LogSystems()
{
    if (!Mac::DiagEnabled())
    {
        return;
    }
    for (const char* name : {"CallbackSystem", "WorldStateSystem", "ScriptableServiceContainer"})
    {
        MAC_DIAG( "[diag] system %s map=%d\n", name, SystemInMap(name) ? 1 : 0);
    }

    auto* rtti = RED4ext::CRTTISystem::Get();
    auto* gameType = rtti ? rtti->GetClass(RED4ext::CName("ScriptGameInstance")) : nullptr;
    bool found = false;
    if (gameType)
    {
        const RED4ext::CName want("GetCallbackSystem");
        for (uint32_t i = 0; i < gameType->staticFuncs.Size(); ++i)
        {
            auto* fn = gameType->staticFuncs[i];
            if (fn && fn->shortName == want)
            {
                found = true;
                break;
            }
        }
    }
    MAC_DIAG( "[diag] GetCallbackSystem static=%d\n", found ? 1 : 0);
}

void DumpBytes(const char* aLabel, const char* aText)
{
    MAC_DIAG( "[selftest] %s hex", aLabel);
    if (!aText)
    {
        std::fprintf(stderr, " null\n");
        return;
    }
    for (const auto* p = reinterpret_cast<const unsigned char*>(aText); *p; ++p)
    {
        std::fprintf(stderr, " %02x", *p);
    }
    std::fprintf(stderr, "\n");
}

void RunSelfTest()
{
    if (!Mac::DiagEnabled())
    {
        return;
    }
    const char* inputText = "\xC3\x84" "BC";
    const char* expected = "\xC3\xA4" "bc";

    Red::CString input(inputText);
    Red::ScriptRef<Red::CString> ref(false);
    ref.ref = &input;
    ref.managed = false;

    Red::CString lower;
    const bool called = Red::CallGlobal("UTF8StrLower", lower, ref);
    const bool matched = called && lower.c_str() && std::strcmp(lower.c_str(), expected) == 0;
    MAC_DIAG( "[selftest] lower ok=%d text=%s\n", matched ? 1 : 0, lower.c_str() ? lower.c_str() : "");
    if (!matched)
    {
        DumpBytes("lower", lower.c_str());
        Red::CString direct = App::UTF8StrLower(ref);
        const bool directOk = direct.c_str() && std::strcmp(direct.c_str(), expected) == 0;
        MAC_DIAG( "[selftest] lower direct ok=%d text=%s\n", directOk ? 1 : 0,
                     direct.c_str() ? direct.c_str() : "");
        if (!directOk)
        {
            DumpBytes("lower direct", direct.c_str());
        }
    }

    const char* archive = "archive/Mac/content/basegame_1_engine.archive";
    Red::CString path(archive);
    Red::ScriptRef<Red::CString> pathRef(false);
    pathRef.ref = &path;
    pathRef.managed = false;
    bool exists = false;
    const bool fileCalled = Red::CallGlobal("GameFileExists", exists, pathRef);
    MAC_DIAG( "[selftest] file ok=%d exists=%d path=%s\n", (fileCalled && exists) ? 1 : 0, exists ? 1 : 0,
                 archive);

    Red::Handle<App::CallbackSystem> callback;
    const bool callbackCalled = Red::CallStatic("ScriptGameInstance", "GetCallbackSystem", callback);
    MAC_DIAG( "[selftest] callback ok=%d nonnull=%d\n", (callbackCalled && callback) ? 1 : 0,
                 callback ? 1 : 0);

    Red::CString version;
    const bool versionCalled = Red::CallStatic("Codeware", "Version", version);
    const bool versionOk = versionCalled && version.c_str() && version.c_str()[0] != '\0';
    MAC_DIAG( "[selftest] version ok=%d text=%s\n", versionOk ? 1 : 0,
                 version.c_str() ? version.c_str() : "");
}
}

void Red::MacPublishGlobal(RED4ext::CRTTISystem* aRtti, const char* aName, RED4ext::CGlobalFunction* aFunc)
{
    using Map = RED4ext::HashMap<RED4ext::CName, RED4ext::CGlobalFunction*>;
    auto* map = reinterpret_cast<Map*>(reinterpret_cast<uint8_t*>(aRtti) + 0xA0);
    const auto name = RED4ext::CName(aName);
    auto plausible = [](const void* aPtr) {
        const auto value = reinterpret_cast<uintptr_t>(aPtr);
        return value > 0x100000000ULL && (value % 8) == 0;
    };
    const bool shape = map->capacity >= 16 && map->capacity <= 100000 && map->size > 0 && map->size < map->capacity &&
                       map->nodeList.stride == sizeof(typename Map::Node) && plausible(map->indexTable) &&
                       plausible(map->nodeList.nodes);
    auto* known = aRtti->GetFunction(RED4ext::CName("GetGameInstance"));
    auto** slot = shape ? map->Get(RED4ext::CName("GetGameInstance")) : nullptr;
    const bool mapOk = shape && known && slot && *slot == known;
    int inserted = 0;
    if (mapOk)
    {
        const auto pair = map->Insert(name, aFunc);
        inserted = pair.second ? 1 : 0;
    }
    auto** cnameSlot = shape ? map->Get(name) : nullptr;
    auto* found = aRtti->GetFunction(name);

    // GetFunction can miss a name that the CName map already holds. The SDK's
    // second table is HashMap<uint64_t, CGlobalFunction*> at +0xD0, keyed by the
    // CName hash. Insert only when that table resolves GetGameInstance to the
    // same pointer the virtual returns.
    using HashMap64 = RED4ext::HashMap<uint64_t, RED4ext::CGlobalFunction*>;
    auto* byHash = reinterpret_cast<HashMap64*>(reinterpret_cast<uint8_t*>(aRtti) + 0xD0);
    const bool hashShape = byHash->capacity >= 16 && byHash->capacity <= 100000 && byHash->size > 0 &&
                           byHash->size < byHash->capacity && byHash->nodeList.stride == sizeof(typename HashMap64::Node) &&
                           plausible(byHash->indexTable) && plausible(byHash->nodeList.nodes);
    const auto knownHash = static_cast<uint64_t>(RED4ext::CName("GetGameInstance"));
    auto** hashKnown = hashShape ? byHash->Get(knownHash) : nullptr;
    const bool hashOk = hashShape && known && hashKnown && *hashKnown == known;
    int hashInserted = 0;
    if (hashOk && !found)
    {
        const auto pair = byHash->Insert(static_cast<uint64_t>(name), aFunc);
        hashInserted = pair.second ? 1 : 0;
        found = aRtti->GetFunction(name);
    }
    MAC_DIAG(
                 "[cw] global %s publish shape=%d map=%d inserted=%d cname=%p func=%p found=%d hashShape=%d hashOk=%d "
                 "hashInserted=%d stride=%u size=%u cap=%u short=%llx\n",
                 aName, shape ? 1 : 0, mapOk ? 1 : 0, inserted, cnameSlot ? static_cast<void*>(*cnameSlot) : nullptr,
                 static_cast<void*>(aFunc), found ? 1 : 0, hashShape ? 1 : 0, hashOk ? 1 : 0, hashInserted,
                 map->nodeList.stride, map->size, map->capacity,
                 static_cast<unsigned long long>(aFunc ? aFunc->shortName.hash : 0));
}

namespace
{
bool PointerExecutable(uintptr_t aPtr)
{
    if (aPtr < 0x100000000ULL || (aPtr & 3) != 0)
    {
        return false;
    }
    vm_address_t addr = static_cast<vm_address_t>(aPtr);
    vm_size_t size = 0;
    vm_region_basic_info_data_64_t info{};
    mach_msg_type_number_t count = VM_REGION_BASIC_INFO_COUNT_64;
    mach_port_t object = MACH_PORT_NULL;
    const kern_return_t kr = vm_region_64(mach_task_self(), &addr, &size, VM_REGION_BASIC_INFO_64,
                                          reinterpret_cast<vm_region_info_t>(&info), &count, &object);
    return kr == KERN_SUCCESS && addr <= aPtr && (info.protection & VM_PROT_EXECUTE) != 0;
}

bool GameInstanceMapReady(RED4ext::GameInstance* aGi, unsigned* aSize, unsigned* aCap, unsigned* aStride)
{
    using Map = RED4ext::HashMap<RED4ext::CBaseRTTIType*, RED4ext::Handle<RED4ext::IScriptable>>;
    auto* map = reinterpret_cast<Map*>(reinterpret_cast<uint8_t*>(aGi) + 0x08);
    const unsigned stride = map->nodeList.stride;
    const unsigned cap = map->capacity;
    const unsigned size = map->size;
    if (aSize)
    {
        *aSize = size;
    }
    if (aCap)
    {
        *aCap = cap;
    }
    if (aStride)
    {
        *aStride = stride;
    }
    return stride == sizeof(typename Map::Node) && cap >= 4 && cap <= 100000 && size <= cap && map->indexTable &&
           map->nodeList.nodes;
}

bool RangeReadable(uint64_t aAddr, uint64_t aLen)
{
    if (aAddr < 0x100000000ULL || aLen == 0)
    {
        return false;
    }
    vm_address_t addr = static_cast<vm_address_t>(aAddr);
    vm_size_t size = 0;
    vm_region_basic_info_data_64_t info{};
    mach_msg_type_number_t count = VM_REGION_BASIC_INFO_COUNT_64;
    mach_port_t object = MACH_PORT_NULL;
    const kern_return_t kr = vm_region_64(mach_task_self(), &addr, &size, VM_REGION_BASIC_INFO_64,
                                          reinterpret_cast<vm_region_info_t>(&info), &count, &object);
    return kr == KERN_SUCCESS && addr <= aAddr && addr + size >= aAddr + aLen && (info.protection & VM_PROT_READ) != 0;
}

bool DescribeGameInstance(uint64_t aObj, unsigned* aSize, unsigned* aCap, unsigned* aStride, uintptr_t* aVt)
{
    *aSize = 0;
    *aCap = 0;
    *aStride = 0;
    *aVt = 0;
    if ((aObj & 0xF) != 0 || !RangeReadable(aObj, 0x138))
    {
        return false;
    }
    *aVt = *reinterpret_cast<const uintptr_t*>(static_cast<uintptr_t>(aObj));
    auto* gi = reinterpret_cast<RED4ext::GameInstance*>(static_cast<uintptr_t>(aObj));
    const bool ready = GameInstanceMapReady(gi, aSize, aCap, aStride);
    return ready && PointerExecutable(*aVt);
}

void CallGetGameInstanceNative(RED4ext::CGlobalFunction* aFunc, RED4ext::ScriptGameInstance* aOut, void* aPair,
                               const char*& aHow)
{
    auto* retType = (aFunc->returnType && aFunc->returnType->type) ? aFunc->returnType->type
                                                                    : Red::ResolveType<RED4ext::ScriptGameInstance>();
    if (!retType || retType->GetSize() != sizeof(RED4ext::ScriptGameInstance) || aFunc->params.Size() != 0)
    {
        aHow = "no-rettype";
        return;
    }

    char code[264]{};
    RED4ext::CStackFrame frame(nullptr, code);
    *frame.code = 38;
    frame.code = code;
    frame.func = aFunc;
    frame.unk28 = reinterpret_cast<int64_t>(aPair);

    static RED4ext::IScriptable* dummy = nullptr;
    if (!dummy)
    {
        if (auto* ent = RED4ext::CRTTISystem::Get()->GetClass(RED4ext::CName("entEntity")))
        {
            dummy = static_cast<RED4ext::IScriptable*>(ent->CreateInstance(true));
        }
    }

    if (aFunc->flags.isNative)
    {
        const bool exec = Red::Detail::CallFunctionWithFrame(aFunc, dummy, &frame, aOut, retType);
        aHow = exec ? "frame" : "frame-fail";
        if (aOut->instance)
        {
            return;
        }
        frame.code = code;
        *frame.code = 38;
    }

    // InternalExecute skips the native body when the import has not set
    // isNative yet. The handler slot is the existing OpcodeHandlers table.
    const uintptr_t table = static_cast<uintptr_t>(_dyld_get_image_vmaddr_slide(0)) + 0x10908B798ULL;
    const uint32_t reg = aFunc->regIndex;
    if (reg == 0 || reg > 10000 || !PointerExecutable(table))
    {
        if (!aHow || aHow[0] == '\0' || std::strcmp(aHow, "none") == 0)
        {
            aHow = "no-handler";
        }
        return;
    }
    auto* slot = reinterpret_cast<RED4ext::OpcodeHandlers::Handler_t*>(table) + reg;
    auto handler = *slot;
    if (!PointerExecutable(reinterpret_cast<uintptr_t>(handler)))
    {
        aHow = "handler-miss";
        return;
    }
    handler(dummy, &frame, aOut, retType);
    aHow = aOut->instance ? "handler" : "handler-null";
}
}

namespace
{
// The derived GameInstance constructor (C1 wrapper). It calls the base constructor 0x3313F4C, then
// sets vtable 0x6FB1FA0. The base constructor writes pair at +0x100; the game's
// GetGameInstance native (0x1F42944) reads that pair through CStackFrame+0x28. The base
// constructor writes {0x415643ff7b, this}.
constexpr uintptr_t kGameInstanceCtorRva = 0x1691AEC;
// Return address of the call in the CGameFramework constructor (0x3F0D2AC), which stores the
// instance at framework+0x10. The other three callers belong to other app types.
constexpr uintptr_t kFrameworkCtorSiteRva = 0x1577C2C;
constexpr uint64_t kGameInstanceMagic = 0x415643ff7bULL; // mov #0xff7b; movk #0x5643, lsl 16; movk #0x41, lsl 32

using GameInstanceCtor_t = void* (*)(void*);
using GameInstanceRaw_t = RED4ext::GameInstance*;
GameInstanceCtor_t g_gameInstanceCtor = nullptr;
std::atomic<RED4ext::GameInstance*> g_ctorGameInstance{nullptr};
std::atomic<bool> g_postLoadScriptsRan{false};

uintptr_t GameRva(uintptr_t aAddress)
{
    return aAddress - GameBase();
}

bool LooksLikeGameInstance(const void* aPtr)
{
    if (!aPtr)
        return false;
    const auto* bytes = reinterpret_cast<const uint8_t*>(aPtr);
    return *reinterpret_cast<const uint64_t*>(bytes + 0x100) == kGameInstanceMagic &&
           *reinterpret_cast<const void* const*>(bytes + 0x108) == aPtr;
}

void* OnGameInstanceCtor(void* aThis)
{
    const auto caller = GameRva(reinterpret_cast<uintptr_t>(__builtin_return_address(0)));
    auto* result = g_gameInstanceCtor(aThis);
    const bool framework = caller == kFrameworkCtorSiteRva;
    const bool valid = LooksLikeGameInstance(aThis);
    MAC_DIAG("[cw] GameInstance ctor this=%p caller=0x%lx framework=%d valid=%d postLoad=%d\n", aThis,
             static_cast<unsigned long>(caller), framework ? 1 : 0, valid ? 1 : 0, g_postLoadScriptsRan.load() ? 1 : 0);
    // Under a gum classic hook the return address is a gum thunk, so the caller check is informational.
    // Retail runs only the framework path (one construction per boot); keep the first valid instance.
    GameInstanceRaw_t expected = nullptr;
    if (valid && g_ctorGameInstance.compare_exchange_strong(expected, static_cast<RED4ext::GameInstance*>(aThis)))
    {
        if (g_postLoadScriptsRan.load())
        {
            // The instance arrived after codeware_postLoadScripts; register the re-queued systems now.
            try
            {
                Red::TypeInfoRegistrar::RunPending();
                MAC_DIAG("[cw] GameInstance late RunPending done\n");
                LogSystems();
            }
            catch (...)
            {
                std::fprintf(stderr, "[cw] GameInstance late RunPending exception\n");
            }
        }
    }
    return result;
}
}

bool Red::MacInstallGameInstanceHook()
{
    // Through the Core hooking driver (MacHookingDriver), the same path every Raw hook takes.
    // GameBase() finds the Cyberpunk2077 image by name; image index 0 is not always the game.
    auto target = GameBase() + kGameInstanceCtorRva;
    const bool ok = Core::HookingDriver::GetDefault().HookAttach(target, reinterpret_cast<void*>(&OnGameInstanceCtor),
                                                                 reinterpret_cast<void**>(&g_gameInstanceCtor));
    MAC_DIAG_UNLESS(ok, "[cw] GameInstance hook attach=%d target=%p original=%p\n", ok ? 1 : 0,
                    reinterpret_cast<void*>(target), reinterpret_cast<void*>(g_gameInstanceCtor));
    return ok;
}

void Red::MacMarkPostLoadScripts()
{
    g_postLoadScriptsRan.store(true);
}

RED4ext::GameInstance* Red::MacGameInstance()
{
    static std::atomic<int> logged{0};
    auto* gameInstance = g_ctorGameInstance.load();
    if (gameInstance && !LooksLikeGameInstance(gameInstance))
    {
        gameInstance = nullptr;
    }
    const int state = gameInstance ? 2 : 1;
    if (logged.exchange(state) != state)
    {
        MAC_DIAG("[cw] MacGameInstance %p\n", static_cast<void*>(gameInstance));
    }
    return gameInstance;
}

// R22. Hand-off to the ArchiveXL plugin (see codeware_mac_runtime_system_at in MacEngine.cpp).
extern "C" __attribute__((visibility("default"))) RED4ext::GameInstance* codeware_mac_game_instance()
{
    return Red::MacGameInstance();
}

extern "C" __attribute__((visibility("default"))) void codeware_registerNatives()
{
    static bool once = false;
    if (once)
    {
        return;
    }
    once = true;

    MAC_DIAG("[cw] codeware_registerNatives enter\n");
    try
    {
        InitVault();
        if (!g_vaultSymbolsOk)
        {
            std::fprintf(stderr, "[cw] vault mismatch, registration skipped\n");
            std::fflush(stderr);
            return;
        }

        // R13/R22. The installed NCC ArchiveXL.dylib registers no script natives, so Codeware registers a stand-in class
        // `ArchiveXL` (macos/ArchiveXLScripts.cpp). In a session with the ported ArchiveXL the real class exists before this
        // point (NATREG runs archivexl_registerNatives first) and the registrar skips the stand-in: a class is never registered twice.
        if (Mac::ArchiveXLClassExists())
        {
            MAC_DIAG("[cw] class ArchiveXL is registered by the ArchiveXL plugin: the stand-in is skipped\n");
        }

        LogPending("register");
        Mac::Lifecycle::RunNativesRegistered(); // RedLibProvider: Red::TypeInfoRegistrar::RunPending()
        Mac::R17AuditPropertyTypes("natives");
        LogClasses();
        LogGlobals();
        MAC_DIAG("[cw] codeware_registerNatives leave\n");
    }
    catch (const std::exception& ex)
    {
        std::fprintf(stderr, "[cw] codeware_registerNatives exception %s\n", ex.what());
    }
    catch (...)
    {
        std::fprintf(stderr, "[cw] codeware_registerNatives exception\n");
    }
    std::fflush(stderr);
}

extern "C" __attribute__((visibility("default"))) void codeware_postLoadScripts()
{
    MAC_DIAG("[cw] codeware_postLoadScripts enter\n");
    try
    {
        // R15. Write the New and Cast opcode handlers when they were not set at plugin load. Before any service runs.
        Mac::PatchScriptOpCodes("postLoadScripts");
        Mac::R16aSelfTest(); // SELFTEST R16a
        Mac::R17SelfTest();  // SELFTEST R17
        Mac::R25SelfTest();  // SELFTEST R25 (CString copy through the SDK row 0x2AACC)
        Mac::EngineSelfTest(); // SELFTEST R18
        g_logGameInstanceShape = true;
        LogPending("post");
        Mac::Lifecycle::RunScriptsLoaded(); // RedLibProvider: Red::TypeInfoRegistrar::RunPending()
        // R22. The Frida script calls only this function after LoadScripts. The ported ArchiveXL plugin, when it is loaded, gets its
        // own post-load step (late types, services) from here, in the same place its natives step ran before the scripts were linked.
        if (auto* axlPost = reinterpret_cast<void (*)()>(dlsym(RTLD_DEFAULT, "archivexl_postLoadScripts")))
        {
            axlPost();
        }
        Red::MacMarkPostLoadScripts();
        LogClasses();
        LogGlobals();
        LogSystems();
        try
        {
            RunSelfTest();
        }
        catch (const std::exception& ex)
        {
            MAC_DIAG( "[selftest] exception %s\n", ex.what());
        }
        catch (...)
        {
            MAC_DIAG( "[selftest] exception\n");
        }
        // R13. Hook counters, the NodeRef and ArchiveXL self-tests, and the 50 s log.
        try
        {
            Mac::R13PostLoadScripts();
        }
        catch (const std::exception& ex)
        {
            MAC_DIAG( "[selftest] r13 exception %s\n", ex.what());
        }
        catch (...)
        {
            MAC_DIAG( "[selftest] r13 exception\n");
        }
        // R14. Start the script services last, after the R13 diag. This is where Lizzie's services get OnLoad.
        try
        {
            Mac::R14StartServices();
        }
        catch (const std::exception& ex)
        {
            std::fprintf(stderr, "[cw] R14 exception %s\n", ex.what());
        }
        catch (...)
        {
            std::fprintf(stderr, "[cw] R14 exception\n");
        }
        // R18 B1. One counting script callback per event kind, registered after the R14 counts are logged so those stay as in Gate 5.
        try
        {
            Mac::R18RegisterEventCallbacks();
        }
        catch (...)
        {
            std::fprintf(stderr, "[cw] R18 callback registration exception\n");
        }
        // R19. B2 and B3 self-tests on this engine thread.
        try
        {
            Mac::R19PostLoadScripts();
        }
        catch (...)
        {
            std::fprintf(stderr, "[cw] R19 post-load tests exception\n");
        }
        // R20. UI: the key translation check (the UI hook checks run inside the hooks on the UI thread).
        try
        {
            Mac::R20PostLoadScripts();
        }
        catch (...)
        {
            std::fprintf(stderr, "[cw] R20 post-load tests exception\n");
        }
        // R18. Job dispatch test: the same thread, the same calls as production, no waiting; checked at t+50s.
        try
        {
            Mac::JobDispatchTest();
        }
        catch (...)
        {
            std::fprintf(stderr, "[cw] R18 job dispatch test exception\n");
        }
        MAC_DIAG("[cw] codeware_postLoadScripts leave\n");
    }
    catch (const std::exception& ex)
    {
        std::fprintf(stderr, "[cw] codeware_postLoadScripts exception %s\n", ex.what());
    }
    catch (...)
    {
        std::fprintf(stderr, "[cw] codeware_postLoadScripts exception\n");
    }
    std::fflush(stderr);
}
