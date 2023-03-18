#pragma once

#include "WidgetBuildingService.hpp"

namespace App
{
struct inkWidgetEx : Red::inkWidget
{
    void SetController(const Red::Handle<Red::inkLogicController>& aController)
    {
        logicController = aController;

        WidgetBuildingService::AttachController(*this, aController);
    }

    void AddSecondaryController(const Red::Handle<Red::inkLogicController>& aController)
    {
        secondaryControllers.PushBack(aController);

        WidgetBuildingService::AttachController(*this, aController);
    }
};
}

RTTI_EXPAND_CLASS(App::inkWidgetEx, Red::inkWidget, {
    RTTI_METHOD(SetController);
    RTTI_METHOD(AddSecondaryController);
});
