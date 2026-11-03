#pragma once

namespace Red
{
struct EventManager {};
}

namespace Raw::inkLayer
{
constexpr auto RegisterListener = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkLayer_RegisterListener,
    /* type = */ void (*)(Red::inkLayer* aLayer, const Red::Handle<Red::IScriptable>& aListener)>();

constexpr auto AttachWidgetTree = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkLayer_AttachWidgetTree,
    /* type = */ uint64_t (*)(Red::inkLayer* aLayer,
                              const Red::Handle<Red::inkWidget>& aWidget,
                              const Red::WeakHandle<Red::inkLayerProxy>& aProxy)>();
}

namespace Raw::inkWidget
{
// Game 2.5 (exe 3.0.88.46235): inkWidget grew to 528 bytes but this is unchanged: inkWidget virtual 0x190
// (0x830D4C) does `lea rbx,[rcx+0x50]` (0x830D70) and passes it to InkWidget_TriggerEvent (0x830D96).
using EventManager = Core::OffsetPtr<0x50, Red::EventManager>;

#if defined(__APPLE__)
// Mac ABI (R20): the layer proxy comes back through x8 and the out argument is gone. The function also caches the proxy in
// widget+0x148 itself (the Windows one does too). GetLayer keeps the Windows call shape for WidgetBuildingService.
constexpr auto GetLayerNative = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidget_GetLayer,
    /* type = */ Red::Handle<Red::inkLayerProxy> (*)(Red::inkWidget* aWidget)>();

struct GetLayerFn
{
    void operator()(Red::inkWidget* aWidget, Red::Handle<Red::inkLayerProxy>& aProxy) const
    {
        aProxy = GetLayerNative(aWidget);
    }
};
inline constexpr GetLayerFn GetLayer{};
#else
constexpr auto GetLayer = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidget_GetLayer,
    /* type = */ void (*)(Red::inkWidget* aWidget, Red::Handle<Red::inkLayerProxy>& aProxy)>();
#endif

constexpr auto SetLayer = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidget_SetLayer,
    /* type = */ void (*)(Red::inkWidget* aWidget, Red::Handle<Red::inkLayerProxy>& aProxy)>();

constexpr auto ScriptReparent = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidget_ScriptReparent,
    /* type = */ void (*)(Red::inkWidget* aWidget, Red::CStackFrame* aFrame, void*, void*)>();

constexpr auto TriggerEvent = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidget_TriggerEvent,
    /* type = */ bool (*)(void* aManager, Red::CName aName, Red::Handle<Red::Event> aObject)>();
}

namespace Raw::inkCompoundWidget
{
constexpr auto ScriptAddChild = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidget_ScriptAddChild,
    /* type = */ void (*)(Red::inkCompoundWidget* aWidget, Red::CStackFrame* aFrame, void*, void*)>();
}

namespace Raw::inkLogicController
{
constexpr auto OnInitialize = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkLogicController_OnInitialize,
    /* type = */ void (*)(Red::inkLogicController* aController)>();

constexpr auto OnUninitialize = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkLogicController_OnUninitialize,
    /* type = */ void (*)(Red::inkLogicController* aController)>();

constexpr auto OnArrangeChildrenComplete = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkLogicController_OnArrangeChildrenComplete,
    /* type = */ void (*)(Red::inkLogicController* aController)>();
}
