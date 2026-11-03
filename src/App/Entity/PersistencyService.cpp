#include "PersistencyService.hpp"
#if defined(__APPLE__)
#include "MacEngine.hpp"
#endif

void App::PersistencyService::OnBootstrap()
{
    HookBefore<Raw::PersistentObject::InitializeState>(&OnInitializeState).OrThrow();
}

void App::PersistencyService::OnInitializeState(Red::PersistentObject* aObject, Red::PersistentStateParams* aParams)
{
#if defined(__APPLE__)
    {
        static auto& counter = Mac::HookCount("PersistentObject_InitializeState");
        Mac::Hit(counter);
    }
#endif
    if (aParams->persistentId.entityID.IsPersistable())
    {
        static const auto s_deviceComponentType = Red::GetClass("gameDeviceComponent");

        if (aParams->objectType->IsA(s_deviceComponentType))
        {
            aParams->mergeStates = true;
        }
    }
}
