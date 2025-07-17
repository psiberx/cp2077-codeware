#pragma once

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
    ink::ISystemRequestsHandler* GetSystemRequestsHandlerPtr();

    uint8_t unk00[0x2E8];                                    // 000
    WeakHandle<ink::Widget> inputWidget;                     // 2E8
    KeyboardState keyboardState;                             // 2F8
    uint8_t unk2FA[0x370 - 0x2FA];                           // 2FA
    WeakHandle<ink::ISystemRequestsHandler> requestsHandler; // 370
    DynArray<SharedPtr<InkLayerManager>> layerManagers;      // 380
};
RED4EXT_ASSERT_OFFSET(InkSystem, inputWidget, 0x2E8);
RED4EXT_ASSERT_OFFSET(InkSystem, keyboardState, 0x2F8);
RED4EXT_ASSERT_OFFSET(InkSystem, requestsHandler, 0x370);
RED4EXT_ASSERT_OFFSET(InkSystem, layerManagers, 0x380);
}

namespace Raw::inkSystem
{
constexpr auto Instance = Core::RawPtr<
    /* addr = */ Red::AddressLib::InkSystem_Instance,
    /* type = */ Red::InkSystem*>();

constexpr auto ProcessInputEvents = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkSystem_ProcessInputEvents,
    /* type = */ void (*)(Red::InkSystem*, uint64_t a2, Red::RawInputBuffer&)>();

constexpr auto ProcessCharacterEvent = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkSystem_ProcessCharacterEvent,
    /* type = */ bool (*)(Red::InkSystem*, Red::EInputKey, Red::EInputAction)>();
}
