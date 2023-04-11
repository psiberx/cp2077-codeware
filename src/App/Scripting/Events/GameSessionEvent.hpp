#pragma once

#include "App/Scripting/EventObject.hpp"

namespace App
{
struct GameSessionEvent : NamedEvent
{
    GameSessionEvent() = default;

    GameSessionEvent(Red::CName aName, bool aPreGame, bool aRestored)
        : NamedEvent(aName)
        , preGame(aPreGame)
        , restored(aRestored)
    {
    }

    bool preGame;
    bool restored;

    RTTI_IMPL_TYPEINFO(App::GameSessionEvent);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::GameSessionEvent, {
    RTTI_PARENT(App::NamedEvent);
    RTTI_GETTER(restored);
    RTTI_GETTER(preGame);
});
