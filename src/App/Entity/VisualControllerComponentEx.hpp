#pragma once

#include "Red/VisualController.hpp"

namespace App
{
struct VisualControllerComponentEx : Red::entVisualControllerComponent
{
    inline bool LoadAppearanceDependencies(Red::Optional<bool> aWait)
    {
        auto& controller = Raw::VisualControllerComponent::Controller::Ref(this);

        if (!controller)
            return false;

        auto update = false;

        for (const auto& componentDependency : appearanceDependency)
        {
            auto found = false;

            for (const auto& controllerDependency : controller->dependencies)
            {
                if (controllerDependency.mesh.path == componentDependency.mesh.path)
                {
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                std::scoped_lock _(controller->lock);

                controller->dependencies.EmplaceBack();

                auto& controllerDependency = controller->dependencies.Back();
                controllerDependency.mesh = componentDependency.mesh;
                controllerDependency.appearanceName = componentDependency.appearanceName;

                update = true;
            }
        }

        if (update)
        {
            Red::JobHandle jobHandle;
            Raw::VisualController::LoadDependencies(controller, jobHandle, 0);

            if (aWait)
            {
                Red::WaitForJob(jobHandle, std::chrono::milliseconds(5000));
            }
        }

        return update;
    }
};
}

RTTI_EXPAND_CLASS(Red::entVisualControllerComponent, App::VisualControllerComponentEx, {
    RTTI_METHOD(LoadAppearanceDependencies);
});
