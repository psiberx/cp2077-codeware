#include "PersistencyService.hpp"

void App::PersistencyService::OnBootstrap()
{
    if (!HookBefore<Raw::PersistentObject::InitializeState>(&OnInitializeState))
        throw std::runtime_error("Failed to hook PersistentObject::InitializeState.");
}

void App::PersistencyService::OnInitializeState(Red::PersistentObject* aObject, Red::PersistentStateParams* aParams)
{
    if (aParams->persistentId.entityID.IsPersistable())
    {
        static const auto s_deviceComponentType = Red::GetClass("gameDeviceComponent");

        if (aParams->objectType->IsA(s_deviceComponentType))
        {
            aParams->mergeStates = true;
        }
    }
}
