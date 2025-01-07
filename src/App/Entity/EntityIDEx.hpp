#pragma once

namespace App
{
struct EntityIDEx : Red::EntityID
{
    static Red::EntityID FromHash(uint64_t aHash)
    {
        return {aHash};
    }

    uint64_t ToHash()
    {
        return hash;
    }
};
}

RTTI_EXPAND_CLASS(Red::EntityID, App::EntityIDEx, {
    RTTI_METHOD(FromHash);
    RTTI_METHOD(ToHash);
});
