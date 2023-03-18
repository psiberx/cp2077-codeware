#pragma once

#include "Core/Foundation/Feature.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Core/Logging/LoggingAgent.hpp"
#include "Red/InkCore.hpp"

namespace App
{
class WidgetBuildingService
    : public Core::Feature
    , public Core::HookingAgent
    , public Core::LoggingAgent
{
public:
    static bool InitializeWidgetTree(const Red::Handle<Red::inkWidget>& aWidget);
    static bool InitializeController(const Red::Handle<Red::inkWidget>& aWidget,
                                     const Red::Handle<Red::inkLogicController>& aController);

protected:
    void OnBootstrap() override;
    void OnShutdown() override;

    static void AfterReparentFromScript(Red::inkWidget* aWidget, Red::CStackFrame*, void*, void*);
    static void AfterAddChildFromScript(Red::inkCompoundWidget* aParent, Red::CStackFrame*, void*, void*);
};
}
