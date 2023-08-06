#pragma once

#include "Red/Addresses.hpp"
#include "Red/Input.hpp"

namespace Red
{
struct InkLayerManager
{
    uint8_t unk00[0x38];               // 00
    DynArray<Handle<inkLayer>> layers; // 38
};
RED4EXT_ASSERT_OFFSET(InkLayerManager, layers, 0x38);

struct InkSystem
{
    static InkSystem* Get();

    InkLayerManager* GetLayerManager();
    DynArray<Handle<inkLayer>>& GetLayers();
    WeakHandle<ink::ISystemRequestsHandler>& GetSystemRequestsHandler();

    uint8_t unk00[0x2B0];                                    // 000
    WeakHandle<ink::Widget> inputWidget;                     // 2B0
    KeyboardState keyboardState;                             // 2C0
    uint8_t unk2C2[0x328 - 0x2C2];                           // 2C2
    WeakHandle<ink::ISystemRequestsHandler> requestsHandler; // 328
    DynArray<SharedPtr<InkLayerManager>> layerManagers;      // 338
};
RED4EXT_ASSERT_OFFSET(InkSystem, inputWidget, 0x2B0);
RED4EXT_ASSERT_OFFSET(InkSystem, keyboardState, 0x2C0);
RED4EXT_ASSERT_OFFSET(InkSystem, requestsHandler, 0x328);
RED4EXT_ASSERT_OFFSET(InkSystem, layerManagers, 0x338);
}

namespace Raw::inkSystem
{
constexpr auto Instance = Core::RawPtr<
    /* addr = */ Red::Addresses::InkSystem_Instance,
    /* type = */ Red::InkSystem*>();

constexpr auto ProcessInputEvents = Core::RawFunc<
    /* addr = */ Red::Addresses::InkSystem_ProcessInputEvents,
    /* type = */ void (*)(Red::InkSystem*, uint64_t a2, Red::RawInputBuffer&)>();

constexpr auto ProcessCharacterEvent = Core::RawFunc<
    /* addr = */ Red::Addresses::InkSystem_ProcessCharacterEvent,
    /* type = */ bool (*)(Red::InkSystem*, Red::EInputKey, Red::EInputAction)>();
}
