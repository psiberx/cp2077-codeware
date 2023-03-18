#pragma once

#include "Red/Addresses.hpp"

namespace Raw::inkLayer
{
constexpr auto RegisterListener = Core::RawFunc<
    /* addr = */ Red::Addresses::InkLayer_RegisterListener,
    /* type = */ void (*)(Red::inkLayer* aLayer, const Red::Handle<Red::IScriptable>& aListener)>();

constexpr auto InitializeWidgetTree = Core::RawFunc<
    /* addr = */ Red::Addresses::InkLayer_InitializeWidgetTree,
    /* type = */ void (*)(Red::inkLayer* aLayer, const Red::Handle<Red::inkWidget>& aWidget,
                          const Red::Handle<Red::inkLayerProxy>& aProxy)>();
}

namespace Raw::inkWidget
{
constexpr auto GetLayer = Core::RawFunc<
    /* addr = */ Red::Addresses::InkWidget_GetLayer,
    /* type = */ void (*)(Red::inkWidget* aWidget, Red::Handle<Red::inkLayerProxy>& aProxy)>();

constexpr auto SetLayer = Core::RawFunc<
    /* addr = */ Red::Addresses::InkWidget_SetLayer,
    /* type = */ void (*)(Red::inkWidget* aWidget, Red::Handle<Red::inkLayerProxy>& aProxy)>();

constexpr auto ScriptReparent = Core::RawFunc<
    /* addr = */ Red::Addresses::InkWidget_ScriptReparent,
    /* type = */ void (*)(Red::inkWidget* aWidget, Red::CStackFrame* aFrame, void*, void*)>();
}

namespace Raw::inkCompoundWidget
{
constexpr auto ScriptAddChild = Core::RawFunc<
    /* addr = */ Red::Addresses::InkWidget_ScriptAddChild,
    /* type = */ void (*)(Red::inkCompoundWidget* aWidget, Red::CStackFrame* aFrame, void*, void*)>();
}
