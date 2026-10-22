#pragma once

#include "Red/InkSpawner.hpp"

namespace Raw::InkWidgetLibrary
{
// Game 2.5 (exe 3.0.88.46235): RVA 0x208F250, a thunk that passes false as the fifth argument of
// 0x208F270 (`mov byte [rsp+0x28],0; jmp`), so the four-argument shape is unchanged.
constexpr auto AsyncSpawnFromExternal = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidgetLibrary_AsyncSpawnFromExternal,
    /* type = */ bool (*)(
        Red::ink::WidgetLibraryResource& aLibrary,
        Red::InkSpawningInfo& aSpawningInfo,
        Red::ResourcePath aExternalPath,
        Red::CName aItemName)>();

// Game 2.5: RVA 0x208F2E0 takes a fourth argument, a bool (r9b) handed to the spawn request builder
// 0x208F570 (stored with setne at 0x208F63D). The external thunk above passes false for it.
constexpr auto AsyncSpawnFromLocal = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidgetLibrary_AsyncSpawnFromLocal,
    /* type = */ bool (*)(Red::ink::WidgetLibraryResource& aLibrary, Red::InkSpawningInfo& aSpawningInfo,
                          Red::CName aItemName, bool aFlag)>();

constexpr auto SpawnFromExternal = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidgetLibrary_SpawnFromExternal,
    /* type = */ uintptr_t (*)(
        Red::ink::WidgetLibraryResource& aLibrary,
        Red::Handle<Red::ink::WidgetLibraryItemInstance>& aInstance,
        Red::ResourcePath aExternalPath,
        Red::CName aItemName)>();

constexpr auto SpawnFromLocal = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidgetLibrary_SpawnFromLocal,
    /* type = */ uintptr_t (*)(
        Red::ink::WidgetLibraryResource& aLibrary,
        Red::Handle<Red::ink::WidgetLibraryItemInstance>& aInstance,
        Red::CName aItemName)>();
}
