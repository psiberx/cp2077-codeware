#pragma once

#include "Red/InkSpawner.hpp"

namespace Raw::InkWidgetLibrary
{
constexpr auto AsyncSpawnFromExternal = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidgetLibrary_AsyncSpawnFromExternal,
    /* type = */ bool (*)(
        Red::ink::WidgetLibraryResource& aLibrary,
        Red::InkSpawningInfo& aSpawningInfo,
        Red::ResourcePath aExternalPath,
        Red::CName aItemName)>();

constexpr auto AsyncSpawnFromLocal = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidgetLibrary_AsyncSpawnFromLocal,
    /* type = */ bool (*)(
        Red::ink::WidgetLibraryResource& aLibrary,
        Red::InkSpawningInfo& aSpawningInfo,
        Red::CName aItemName)>();

constexpr auto SpawnFromExternal = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidgetLibrary_SpawnFromExternal,
    /* type = */ Red::Handle<Red::ink::WidgetLibraryItemInstance> (Red::ink::WidgetLibraryResource::*)(
        Red::ResourcePath aExternalPath,
        Red::CName aItemName)>();

constexpr auto SpawnFromLocal = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidgetLibrary_SpawnFromLocal,
    /* type = */ Red::Handle<Red::ink::WidgetLibraryItemInstance> (Red::ink::WidgetLibraryResource::*)(
        Red::CName aItemName)>();
}
