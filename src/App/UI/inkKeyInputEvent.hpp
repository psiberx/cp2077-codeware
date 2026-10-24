#pragma once

#include "Red/Input.hpp"

namespace App
{
struct inkKeyInputEvent : Red::inkInputEvent
{
    inkKeyInputEvent()
        : key(Red::EInputKey::IK_None)
        , action(Red::EInputAction::IACT_None)
    {
    }

    inkKeyInputEvent(Red::KeyboardState& aState, Red::EInputKey aKey, Red::EInputAction aAction,
                     const std::string& aCharacter = "")
        : key(aKey)
        , action(aAction)
        , character(aCharacter.data())
    {
        *reinterpret_cast<Red::KeyboardState**>(&unk68) = &aState;
    }

    [[nodiscard]] bool IsCharacter() const
    {
        return character.length;
    }

    Red::EInputKey key;
    Red::EInputAction action;
    Red::CString character;

    RTTI_IMPL_TYPEINFO(inkKeyInputEvent);
    RTTI_IMPL_ALLOCATOR();
};
}

RED4EXT_ASSERT_OFFSET(App::inkKeyInputEvent, key, 0x90);
RED4EXT_ASSERT_OFFSET(App::inkKeyInputEvent, action, 0x94);
RED4EXT_ASSERT_OFFSET(App::inkKeyInputEvent, character, 0x98);
RED4EXT_ASSERT_SIZE(App::inkKeyInputEvent, 0xB8);

RTTI_DEFINE_CLASS(App::inkKeyInputEvent, {
    RTTI_PARENT(Red::inkInputEvent);
    RTTI_PROPERTY(key);
    RTTI_PROPERTY(action);
    RTTI_PROPERTY(character);
    RTTI_GETTER(key);
    RTTI_GETTER(action);
    RTTI_GETTER(character);
    RTTI_METHOD(IsCharacter);
});
