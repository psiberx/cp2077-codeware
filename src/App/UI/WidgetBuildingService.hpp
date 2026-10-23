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
    // Game 2.5 (exe 3.0.88.46235) has its own native inkWidget.AttachController: its handler (0x2092080) sets
    // logicController (+0x128) or appends to secondaryControllers (+0x108), then 0x20B0190 sets the controller's
    // widget and layer proxy, registers it as a layer listener and calls OnInitialize. Script natives bind to
    // the first function of a name (0x6BDB00), the game's, so Codeware no longer registers its own.
    static bool AttachWidgetTree(const Red::Handle<Red::inkWidget>& aWidget);

protected:
    void OnBootstrap() override;
    void OnShutdown() override;

    static void AfterReparentFromScript(Red::inkWidget* aWidget, Red::CStackFrame*, void*, void*);
    static void AfterAddChildFromScript(Red::inkCompoundWidget* aParent, Red::CStackFrame*, void*, void*);
    static void OnInitializeController(Red::inkLogicController* aController);

    inline static bool IsLegacyController(Red::inkLogicController* aController);
};
}
