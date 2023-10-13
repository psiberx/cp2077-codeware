#pragma once

#include "Red/TweakDB.hpp"
#include "Red/WardrobeSystem.hpp"

namespace App
{
struct WardrobeSystemEx : Red::WardrobeSystem
{
    bool ForgetItemID(const Red::ItemID& aItemID)
    {
        auto& store = Raw::WardrobeSystem::ItemStore::Ref(this);
        auto& mutex = Raw::WardrobeSystem::ItemStoreMutex::Ref(this);
        auto key = Red::GetFlatValue<Red::CName>({aItemID.tdbid, ".appearanceName"});

        std::unique_lock _(mutex);
        return store.Remove(key);
    }
};
}

RTTI_EXPAND_CLASS(Red::WardrobeSystem, App::WardrobeSystemEx, {
    RTTI_METHOD(ForgetItemID);
});
