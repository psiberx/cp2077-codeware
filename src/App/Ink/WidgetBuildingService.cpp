#include "WidgetBuildingService.hpp"

void App::WidgetBuildingService::OnBootstrap()
{
    if (!HookAfter<Raw::inkWidget::ScriptReparent>(&AfterReparentFromScript))
        throw std::runtime_error("Failed to hook inkWidget::Reparent.");

    if (!HookAfter<Raw::inkCompoundWidget::ScriptAddChild>(&AfterAddChildFromScript))
        throw std::runtime_error("Failed to hook inkCompoundWidget::AddChild.");

    if (!Hook<Raw::inkLogicController::OnInitialize>(&OnInitializeController))
        throw std::runtime_error("Failed to hook inkLogicController::OnInitialize.");
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
        AttachWidgetTree(*aWidget);
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
    return aController->unk30
           && aController->unk30->propsByName.Get("detachedWidget")
           && aController->unk30->propsByName.Get("gameController");
}
