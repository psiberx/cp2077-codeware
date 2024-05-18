#pragma once

namespace App
{
struct EntityIDEx : Red::EntityID
{
    static Red::EntityID FromHash(uint64_t aHash)
    {
        return {aHash};
    }
};
}

RTTI_EXPAND_CLASS(Red::EntityID, App::EntityIDEx, {
    RTTI_METHOD(FromHash);
});

RTTI_DEFINE_GLOBALS({
    RTTI_FUNCTION(App::EntityIDEx::FromHash, "ToEntityID");
});
