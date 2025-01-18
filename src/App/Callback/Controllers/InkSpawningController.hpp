#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/Events/InkWidgetSpawnEvent.hpp"
#include "App/UI/WidgetSpawningService.hpp"

namespace App
{
class InkSpawningController : public CallbackSystemController
{
public:
    Core::Map<Red::CName, Red::CName> GetEvents() override
    {
        return {
            {WidgetSpawningService::WidgetSpawnEventName, Red::GetTypeName<inkWidgetSpawnEvent>()},
        };
    }

protected:
    bool OnActivateHook() override
    {
        return true;
    }

    bool OnDeactivateHook() override
    {
        return true;
    }

    void OnActivateEvent(Red::CName aEvent) override
    {
        if (aEvent == WidgetSpawningService::WidgetSpawnEventName)
        {
            WidgetSpawningService::ToggleWidgetSpawnEvent(true);
        }
    }

    void OnDeactivateEvent(Red::CName aEvent) override
    {
        if (aEvent == WidgetSpawningService::WidgetSpawnEventName)
        {
            WidgetSpawningService::ToggleWidgetSpawnEvent(false);
        }
    }
};
}
