#pragma once

namespace Red
{
struct InkSpawningRequest
{
    uint8_t unk00[0x48];                             // 00
    CName itemName;                                  // 48
    WeakHandle<ink::Widget> parentWidget;            // 50
    Handle<ink::Widget> rootWidget;                  // 60
    Handle<ink::IWidgetController> gameController;   // 70
    Handle<ink::WidgetLibraryResource> library;      // 80
    Handle<ink::WidgetLibraryItemInstance> instance; // 90
    ResourcePath externalLibrary;                    // A0
    // bool flag;                                    // F8 (2.31)
    // uint8_t status;                               // 1AC (2.5: 0x804E6B, 0x209FC8A; 2.31: 184)
};
RED4EXT_ASSERT_OFFSET(InkSpawningRequest, itemName, 0x48);
RED4EXT_ASSERT_OFFSET(InkSpawningRequest, rootWidget, 0x60);

// Game 2.5 (exe 3.0.88.46235): FinishAsyncSpawn (RVA 0x209FBE0) is reached through the jump thunk
// 0x209F9E0 and reads the request from [ctx+0x10] (0x209FC41 `mov rcx,[rbx+0x10]`, then
// +0x90 instance, +0x60 rootWidget, +0x70 gameController, status byte +0x1AC := 3). The capture copy
// 0x209F9F0 moves 16 bytes at +0x00 and the SharedPtr at +0x10/+0x18. 2.31 had the request at +0x18.
struct InkSpawningContext
{
    uint8_t unk00[0x10];                   // 00
    SharedPtr<InkSpawningRequest> request; // 10
};
RED4EXT_ASSERT_SIZE(InkSpawningContext, 0x20);
RED4EXT_ASSERT_OFFSET(InkSpawningContext, request, 0x10);

struct InkSpawningInfo
{
    uint8_t unk00[0x38];         // 00
    InkSpawningContext* context; // 38
};
RED4EXT_ASSERT_SIZE(InkSpawningInfo, 0x40);
RED4EXT_ASSERT_OFFSET(InkSpawningInfo, context, 0x38);
}

namespace Raw::InkSpawner
{
constexpr auto FinishAsyncSpawn = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkSpawner_FinishAsyncSpawn,
    /* type = */ bool (*)(
        Red::InkSpawningContext& aContext,
        Red::Handle<Red::ink::WidgetLibraryItemInstance>& aInstance)>();
}
