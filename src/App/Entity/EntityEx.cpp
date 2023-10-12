#include "EntityEx.hpp"
#include "Red/MorphTarget.hpp"

bool App::EntityEx::ApplyMorphTarget(Red::CName aTarget, Red::CName aRegion, float aValue)
{
    // constexpr auto MorphTargetManager_ApplyMorphTarget = Core::RawFunc<
    //     /* addr = */ 0x1403D4774 - Red::Addresses::ImageBase,
    //     /* type = */ void (*)(Red::IComponent* aManager, Red::CName aTarget, Red::CName aRegion, float aValue, bool a5)>();

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
