#include "WidgetBuildingService.hpp"
#if defined(__APPLE__)
#include "MacEngine.hpp"
#include "MacR20.hpp"
#include "MacDiag.hpp"
#endif

void App::WidgetBuildingService::OnBootstrap()
{
    HookAfter<Raw::inkWidget::ScriptReparent>(&AfterReparentFromScript).OrThrow();
    HookAfter<Raw::inkCompoundWidget::ScriptAddChild>(&AfterAddChildFromScript).OrThrow();
    Hook<Raw::inkLogicController::OnInitialize>(&OnInitializeController).OrThrow();
}

void App::WidgetBuildingService::OnShutdown()
{
    Unhook<Raw::inkWidget::ScriptReparent>();
    Unhook<Raw::inkCompoundWidget::ScriptAddChild>();
    Unhook<Raw::inkLogicController::OnInitialize>();
}

void App::WidgetBuildingService::AfterReparentFromScript(Red::inkWidget* aWidget, Red::CStackFrame*, void*, void*)
{
#if defined(__APPLE__)
    static auto& counter = Mac::HookCount("InkWidget_ScriptReparent");
    Mac::Hit(counter);
#endif
    if (!aWidget->layerProxy)
    {
        AttachWidgetTree(Red::AsHandle(aWidget));
    }
}

void App::WidgetBuildingService::AfterAddChildFromScript(Red::inkCompoundWidget* aParent, Red::CStackFrame*, void*, void*)
{
#if defined(__APPLE__)
    static auto& counter = Mac::HookCount("InkCompoundWidget_ScriptAddChild");
    Mac::Hit(counter);
#endif
    if (aParent->layerProxy)
    {
        Red::Handle<Red::inkWidget> widget;
        {
            std::shared_lock _(aParent->children->lock);
            widget = *(aParent->children->children.End() - 1);
        }

        AttachWidgetTree(widget);
    }
}

void App::WidgetBuildingService::OnInitializeController(Red::inkLogicController* aController)
{
#if defined(__APPLE__)
    static auto& counter = Mac::HookCount("InkLogicController_OnInitialize");
    Mac::Hit(counter);
#endif
    const bool legacy = IsLegacyController(aController);
    if (!legacy)
    {
        Raw::inkLogicController::OnInitialize(aController);
    }

#if defined(__APPLE__)
    // R20. One-shot read-only check on the UI thread, inside the hook: a controller's widget WeakHandle (+0x40) locks to an
    // inkWidget and the controller's own class is an inkWidgetLogicController (what IsLegacyController just read through
    // propsByName). The first call after boot is a menu controller.
    if (Mac::R20Once("onInitialize"))
    {
        auto* controllerType = aController->GetType();
        static auto* logicType = Red::GetClass("inkWidgetLogicController");
        static auto* widgetType = Red::GetClass("inkWidget");
        auto widget = aController->widget.Lock();
        const bool controllerOk = controllerType && logicType && controllerType->IsA(logicType);
        const bool widgetOk = widget && widget->GetType() && widgetType && widget->GetType()->IsA(widgetType);
        MAC_DIAG( "[selftest] R20 OnInitialize: controller=%p type=%s legacy=%d widget=%p widgetType=%s\n",
                     static_cast<void*>(aController), controllerType ? controllerType->name.ToString() : "-", legacy ? 1 : 0,
                     static_cast<void*>(widget.instance), widget && widget->GetType() ? widget->GetType()->name.ToString() : "-");
        Mac::R20Check(controllerOk, "the first initialized controller is an inkWidgetLogicController");
        Mac::R20Check(widgetOk, "its widget WeakHandle locks to an inkWidget");
    }

    // R20. The layer lookup AttachWidgetTree makes, tried on the widgets of the first controllers that have a parent: GetLayer
    // (Mac form, Handle through x8) walks up the parent chain, caches the proxy in widget+0x148 as the game does lazily, and the
    // proxy's weak layer locks to an inkLayer. Read-only apart from that cache; same thread and context as the production
    // calls. The checks are made at t+50s from the counters (R20CheckAtT50).
    {
        static auto& tries = Mac::HookCount("R20_GetLayer_tries");
        static auto& found = Mac::HookCount("R20_GetLayer_found");
        if (tries.calls.load() < 40)
        {
            auto widget = aController->widget.Lock();
            if (widget && widget->parentWidget.Lock())
            {
                Mac::Hit(tries);
                Red::Handle<Red::inkLayerProxy> proxy;
                Raw::inkWidget::GetLayer(widget.instance, proxy);
                auto layer = proxy ? proxy->layer.Lock() : Red::Handle<Red::inkLayer>();
                static auto* layerType = Red::GetClass("inkLayer");
                if (layer && layer->GetType() && layerType && layer->GetType()->IsA(layerType))
                {
                    Mac::Hit(found);
                    if (Mac::R20Once("getLayer"))
                    {
                        MAC_DIAG( "[selftest] R20 GetLayer: widget=%p (%s) proxy=%p layer=%p (%s) cached=%d\n",
                                     static_cast<void*>(widget.instance), widget->GetType()->name.ToString(),
                                     static_cast<void*>(proxy.instance), static_cast<void*>(layer.instance),
                                     layer->GetType()->name.ToString(), widget->layerProxy.instance == proxy.instance ? 1 : 0);
                    }
                }
            }
        }
    }
#endif
}

bool App::WidgetBuildingService::AttachWidgetTree(const Red::Handle<Red::inkWidget>& aWidget)
{
#if defined(__APPLE__)
    static auto& counter = Mac::HookCount("WidgetBuilding_AttachWidgetTree");
    Mac::Hit(counter);
#endif
    auto& layerProxy = aWidget->layerProxy;

    if (layerProxy)
        return true;

    Raw::inkWidget::GetLayer(aWidget, layerProxy);

    if (!layerProxy)
        return false;

    auto layer = layerProxy->layer.Lock();

    if (!layer)
        return false;

    Raw::inkWidget::SetLayer(aWidget, layerProxy);
    Raw::inkLayer::AttachWidgetTree(layer, aWidget, layerProxy);

    return true;
}

bool App::WidgetBuildingService::AttachController(const Red::Handle<Red::inkWidget>& aWidget,
                                                  const Red::Handle<Red::inkLogicController>& aController)
{
    if (aController->layerProxy.instance)
        return true;

    aController->widget = aWidget;
    aController->layerProxy = aWidget->layerProxy;

    auto& layerProxy = aWidget->layerProxy;

    if (!layerProxy)
        return false;

    auto layer = layerProxy->layer.Lock();

    if (!layer)
        return false;

    Raw::inkLayer::RegisterListener(layer, aController);

    aController->OnInitialize();

    return true;
}

bool App::WidgetBuildingService::IsLegacyController(Red::inkLogicController* aController)
{
    return aController->nativeType
           && aController->nativeType->propsByName.Get("detachedWidget")
           && aController->nativeType->propsByName.Get("gameController");
}
