#pragma once

#include "Red/Addresses.hpp"

namespace Red
{
struct InkLayerManager
{
    uint8_t unk00[0x38];
    DynArray<Handle<inkLayer>> layers; // 38
};
RED4EXT_ASSERT_OFFSET(InkLayerManager, layers, 0x38);

struct InkSystem
{
    static InkSystem* Get();

    InkLayerManager* GetLayerManager();
    DynArray<Handle<inkLayer>>& GetLayers();

    uint8_t unk00[0x338];
    DynArray<SharedPtr<InkLayerManager>> layerManagers; // 338
};
RED4EXT_ASSERT_OFFSET(InkSystem, layerManagers, 0x338);
}

namespace Raw::inkSystem
{
constexpr auto Instance = Core::RawPtr<
    /* addr = */ Red::Addresses::InkSystem_Instance,
    /* type = */ Red::InkSystem*>();
}
