#pragma once

namespace App
{
struct PersistentIDEx : Red::PersistentID
{
    static Red::PersistentID ForEntity(Red::EntityID aEntityID)
    {
        return {aEntityID};
    }

    static Red::PersistentID ForComponent(Red::EntityID aEntityID, Red::CName aComponent)
    {
        return {aEntityID, aComponent};
    }

    uint64_t ToHash()
    {
        return GetHash();
    }
};
}

RTTI_EXPAND_CLASS(Red::PersistentID, App::PersistentIDEx, {
    RTTI_METHOD(ForEntity);
    RTTI_METHOD(ForComponent);
    RTTI_METHOD(ToHash);
});
