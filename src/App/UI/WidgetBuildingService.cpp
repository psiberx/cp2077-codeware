#include "WidgetBuildingService.hpp"

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
    if (!aWidget->layerProxy)
    {
        AttachWidgetTree(Red::AsHandle(aWidget));
    }
}

void App::WidgetBuildingService::AfterAddChildFromScript(Red::inkCompoundWidget* aParent, Red::CStackFrame*, void*, void*)
{
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
    if (!IsLegacyController(aController))
    {
        Raw::inkLogicController::OnInitialize(aController);
    }
}

bool App::WidgetBuildingService::AttachWidgetTree(const Red::Handle<Red::inkWidget>& aWidget)
{
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
