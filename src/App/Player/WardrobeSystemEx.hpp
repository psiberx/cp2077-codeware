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
        auto success = store.Remove(key);

        if (!success)
        {
            Core::Vector<Red::CName> otherKeys;
            store.ForEach([&otherKeys, &aItemID](const Red::CName& aStoreKey, const Red::ItemID& aStoreItemID)
                          {
                              if (aItemID.tdbid == aStoreItemID.tdbid)
                              {
                                  otherKeys.push_back(aStoreKey);
                              }
                          });

            for (const auto& otherKey : otherKeys)
            {
                if (store.Remove(otherKey))
                {
                    success = true;
                }
            }
        }

        return success;
    }
};
}

RTTI_EXPAND_CLASS(Red::WardrobeSystem, App::WardrobeSystemEx, {
    RTTI_METHOD(ForgetItemID);
});
