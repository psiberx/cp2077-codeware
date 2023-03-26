#pragma once

#include "Core/Foundation/Feature.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/PersistentObject.hpp"

namespace App
{
class PersistencyService
    : public Core::Feature
    , public Core::HookingAgent
{
protected:
    void OnBootstrap() override;

    static void OnInitializeState(Red::PersistentObject* aObject, Red::PersistentStateParams* aParams);
};
}
