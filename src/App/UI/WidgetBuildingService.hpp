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
    static bool AttachWidgetTree(const Red::Handle<Red::inkWidget>& aWidget);
    static bool AttachController(const Red::Handle<Red::inkWidget>& aWidget,
                                 const Red::Handle<Red::inkLogicController>& aController);

protected:
    void OnBootstrap() override;
    void OnShutdown() override;

    static void AfterReparentFromScript(Red::inkWidget* aWidget, Red::CStackFrame*, void*, void*);
    static void AfterAddChildFromScript(Red::inkCompoundWidget* aParent, Red::CStackFrame*, void*, void*);
    static void OnInitializeController(Red::inkLogicController* aController);

    inline static bool IsLegacyController(Red::inkLogicController* aController);
};
}
