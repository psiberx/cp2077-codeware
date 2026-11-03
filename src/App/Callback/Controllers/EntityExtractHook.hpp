#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/MacHooks.hpp"
#include "App/Callback/Events/EntityBuilderEvent.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/EntityBuilder.hpp"

namespace App
{
class EntityExtractHook
    : public CallbackSystemController
    , public Core::HookingAgent
{
public:
    constexpr static auto EventName = Red::CName("Entity/Extract");

    Core::Map<Red::CName, Red::CName> GetEvents() override
    {
        return {{EventName, Red::GetTypeName<EntityBuilderEvent>()}};
    }

protected:
#if defined(__APPLE__)
    // R18. The hooks are installed once at plugin load (InstallMacCallbackHooks); activation has nothing to do.
public:
    static bool InstallMacHook()
    {
        const bool ok = IsHooked<Raw::EntityBuilder::ExtractComponentsJob>()
            || HookBefore<Raw::EntityBuilder::ExtractComponentsJob>(&OnExtractComponentsJob);
        MacHooks::LogInstalled("EntityExtractHook EntityBuilder::ExtractComponentsJob", Raw::EntityBuilder::ExtractComponentsJob.GetOriginalAddress(), ok);
        return ok;
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
#else
    bool OnActivateHook() override
    {
        return IsHooked<Raw::EntityBuilder::ExtractComponentsJob>()
            || HookBefore<Raw::EntityBuilder::ExtractComponentsJob>(&OnExtractComponentsJob);
    }

    bool OnDeactivateHook() override
    {
        return !IsHooked<Raw::EntityBuilder::ExtractComponentsJob>()
            || Unhook<Raw::EntityBuilder::ExtractComponentsJob>();
    }
#endif

    inline static void OnExtractComponentsJob(Red::EntityBuilderJobParams* aParams, void*)
    {
        MAC_HOOK_ENTER("EntityBuilder_ExtractComponentsJob");
        if (!aParams->entityBuilderWeak.Expired())
        {
            CallbackSystem::Get()->DispatchNativeEvent<EntityBuilderEvent>(EventName, aParams->entityBuilderWeak);
        }
    }
};
}
