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

    uint8_t unk00[0x2E8];                                    // 000
    WeakHandle<ink::Widget> inputWidget;                     // 2E8
    KeyboardState keyboardState;                             // 2F8
    uint8_t unk2FA[0x360 - 0x2FA];                           // 2FA
    WeakHandle<ink::ISystemRequestsHandler> requestsHandler; // 360
    DynArray<SharedPtr<InkLayerManager>> layerManagers;      // 370
};
RED4EXT_ASSERT_OFFSET(InkSystem, inputWidget, 0x2E8);
RED4EXT_ASSERT_OFFSET(InkSystem, keyboardState, 0x2F8);
RED4EXT_ASSERT_OFFSET(InkSystem, requestsHandler, 0x360);
RED4EXT_ASSERT_OFFSET(InkSystem, layerManagers, 0x370);
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
