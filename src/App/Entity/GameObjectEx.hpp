#pragma once

namespace App
{
struct GameObjectEx : Red::GameObject
{
    void AddTag(RED4ext::CName tag)
    {
        tags.tags.PushBack(tag);
    }
};
}

RTTI_EXPAND_CLASS(Red::GameObject, App::GameObjectEx, {
    RTTI_METHOD(AddTag);
});
