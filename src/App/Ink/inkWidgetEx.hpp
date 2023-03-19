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

        WidgetBuildingService::AttachController(*this, aController);
    }
};
}

RTTI_EXPAND_CLASS(App::inkWidgetEx, Red::inkWidget, {
    RTTI_METHOD(AttachController);
});
