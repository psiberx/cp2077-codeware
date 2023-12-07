#include "EntityEx.hpp"
#include "Red/MorphTarget.hpp"

bool App::EntityEx::ApplyMorphTarget(Red::CName aTarget, Red::CName aRegion, float aValue)
{
    for (const auto& component : GetComponents())
    {
        if (component->GetType()->IsA(Red::GetType<Red::entMorphTargetManagerComponent>()))
        {
            Raw::MorphTargetManager::ApplyMorphTarget(component, aTarget, aRegion, aValue, false);
            return true;
        }
    }
    return false;
}
