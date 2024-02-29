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
using EventManager = Core::OffsetPtr<0x50, Red::EventManager>;

constexpr auto GetLayer = Core::RawFunc<
    /* addr = */ Red::AddressLib::InkWidget_GetLayer,
    /* type = */ void (*)(Red::inkWidget* aWidget, Red::Handle<Red::inkLayerProxy>& aProxy)>();

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
