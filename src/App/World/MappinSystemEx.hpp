#pragma once

#include "Red/MappinSystem.hpp"

namespace App
{
struct MappinSystemEx : Red::MappinSystem
{
    Red::DynArray<Red::Handle<Red::IMappin>> GetAllMappins()
    {
        Red::DynArray<Red::Handle<Red::IMappin>> mappins;

        {
            std::unique_lock _(Raw::MappinSystem::MappinsLock::Ref(this));
            for (const auto& mappinData : Raw::MappinSystem::MappinsData::Ref(this))
            {
                mappins.PushBack(mappinData.instance);
            }
        }

        return mappins;
    }
};
}

RTTI_EXPAND_CLASS(Red::MappinSystem, App::MappinSystemEx, {
    RTTI_METHOD(GetAllMappins);
});
