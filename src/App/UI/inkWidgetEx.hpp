#pragma once

#include "WidgetBuildingService.hpp"

namespace App
{
struct inkWidgetEx : Red::inkWidget
{
    void AttachController(const Red::Handle<Red::inkLogicController>& aController, Red::Optional<bool> aSecondary)
    {
        if (aSecondary)
        {
            secondaryControllers.PushBack(aController);
        }
        else
        {
            logicController = aController;
        }

        WidgetBuildingService::AttachController(Red::AsHandle(this), aController);
    }
};
}

// Patch 2.5 provides a native inkWidget.AttachController with different parameter names,
// registering Codeware's version as well breaks script binding.
// RTTI_EXPAND_CLASS(Red::inkWidget, App::inkWidgetEx, {
//     RTTI_METHOD(AttachController);
// });
