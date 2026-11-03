#pragma once

#include "Red/InkSpawner.hpp"

namespace Raw::InkWidgetLibrary
{
#if defined(__APPLE__)
// Mac ABI (R20). SpawnFromLocal/SpawnFromExternal return their Handle through x8 and have no out argument; the Windows
// uintptr_t result (the out pointer) does not exist. The two Async* functions take one more bool than the Windows
// declarations (always 0 from the game's callers on AsyncSpawnFromExternal, a real flag on AsyncSpawnFromLocal).
// The *Native objects are the hook targets and the calls to the original. SpawnFromLocal/SpawnFromExternal keep the Windows
// call shape for the services through the wrappers below.
constexpr auto SpawnFromLocalNative = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidgetLibrary_SpawnFromLocal,
    /* type = */ Red::Handle<Red::ink::WidgetLibraryItemInstance> (*)(
        Red::ink::WidgetLibraryResource& aLibrary,
        Red::CName aItemName)>();

constexpr auto SpawnFromExternalNative = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidgetLibrary_SpawnFromExternal,
    /* type = */ Red::Handle<Red::ink::WidgetLibraryItemInstance> (*)(
        Red::ink::WidgetLibraryResource& aLibrary,
        Red::ResourcePath aExternalPath,
        Red::CName aItemName)>();

constexpr auto AsyncSpawnFromLocal = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidgetLibrary_AsyncSpawnFromLocal,
    /* type = */ bool (*)(
        Red::ink::WidgetLibraryResource& aLibrary,
        Red::InkSpawningInfo& aSpawningInfo,
        Red::CName aItemName,
        bool aFlag)>();

constexpr auto AsyncSpawnFromExternal = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidgetLibrary_AsyncSpawnFromExternal,
    /* type = */ bool (*)(
        Red::ink::WidgetLibraryResource& aLibrary,
        Red::InkSpawningInfo& aSpawningInfo,
        Red::ResourcePath aExternalPath,
        Red::CName aItemName,
        bool aFlag)>();

struct SpawnFromLocalFn
{
    uintptr_t operator()(Red::ink::WidgetLibraryResource& aLibrary,
                         Red::Handle<Red::ink::WidgetLibraryItemInstance>& aInstance,
                         Red::CName aItemName) const
    {
        aInstance = SpawnFromLocalNative(aLibrary, aItemName);
        return reinterpret_cast<uintptr_t>(&aInstance);
    }
};
inline constexpr SpawnFromLocalFn SpawnFromLocal{};

struct SpawnFromExternalFn
{
    uintptr_t operator()(Red::ink::WidgetLibraryResource& aLibrary,
                         Red::Handle<Red::ink::WidgetLibraryItemInstance>& aInstance,
                         Red::ResourcePath aExternalPath,
                         Red::CName aItemName) const
    {
        aInstance = SpawnFromExternalNative(aLibrary, aExternalPath, aItemName);
        return reinterpret_cast<uintptr_t>(&aInstance);
    }
};
inline constexpr SpawnFromExternalFn SpawnFromExternal{};
#else
// Game 2.5 (exe 3.0.88.46235): RVA 0x208F250, a thunk that passes false as the fifth argument of
// 0x208F270 (`mov byte [rsp+0x28],0; jmp`), so the four-argument shape is unchanged.
constexpr auto AsyncSpawnFromExternal = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidgetLibrary_AsyncSpawnFromExternal,
    /* type = */ bool (*)(Red::inkWidgetLibraryResource& aLibrary,
                          Red::InkSpawningInfo& aSpawningInfo,
                          Red::ResourcePath aExternalPath,
                          Red::CName aItemName)>();

// Game 2.5: RVA 0x208F2E0 takes a fourth argument, a bool (r9b) handed to the spawn request builder
// 0x208F570 (stored with setne at 0x208F63D). The external thunk above passes false for it.
constexpr auto AsyncSpawnFromLocal = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidgetLibrary_AsyncSpawnFromLocal,
    /* type = */ bool (*)(Red::inkWidgetLibraryResource& aLibrary,
                          Red::InkSpawningInfo& aSpawningInfo,
                          Red::CName aItemName,
                          bool aFlag)>();

constexpr auto SpawnFromExternal = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidgetLibrary_SpawnFromExternal,
    /* type = */ uintptr_t (*)(Red::inkWidgetLibraryResource& aLibrary,
                               Red::Handle<Red::inkWidgetLibraryItemInstance>& aInstance,
                               Red::ResourcePath aExternalPath,
                               Red::CName aItemName)>();

constexpr auto SpawnFromLocal = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidgetLibrary_SpawnFromLocal,
    /* type = */ uintptr_t (*)(Red::inkWidgetLibraryResource& aLibrary,
                               Red::Handle<Red::inkWidgetLibraryItemInstance>& aInstance,
                               Red::CName aItemName)>();
#endif
}
