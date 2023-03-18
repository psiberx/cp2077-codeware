#include "WidgetBuildingService.hpp"

void App::WidgetBuildingService::OnBootstrap()
{
    if (!HookAfter<Raw::inkWidget::ScriptReparent>(&AfterReparentFromScript))
        throw std::runtime_error("Failed to hook inkWidget::Reparent.");

    if (!HookAfter<Raw::inkCompoundWidget::ScriptAddChild>(&AfterAddChildFromScript))
        throw std::runtime_error("Failed to hook inkCompoundWidget::AddChild.");
}

void App::WidgetBuildingService::OnShutdown()
{
    Unhook<Raw::inkWidget::ScriptReparent>();
}

void App::WidgetBuildingService::AfterReparentFromScript(Red::inkWidget* aWidget, Red::CStackFrame*, void*, void*)
{
    if (!aWidget->layerProxy)
    {
        InitializeWidgetTree(*aWidget);
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

        InitializeWidgetTree(widget);
    }
}

bool App::WidgetBuildingService::InitializeWidgetTree(const Red::Handle<Red::inkWidget>& aWidget)
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
    Raw::inkLayer::InitializeWidgetTree(layer, aWidget, layerProxy);

    return true;
}

bool App::WidgetBuildingService::InitializeController(const Red::Handle<Red::inkWidget>& aWidget,
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
