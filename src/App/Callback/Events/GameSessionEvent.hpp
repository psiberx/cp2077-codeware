#pragma once

#include "App/Callback/CallbackSystemEvent.hpp"

namespace App
{
struct GameSessionEvent : CallbackSystemEvent
{
    GameSessionEvent() = default;

    GameSessionEvent(Red::CName aName, bool aPreGame, bool aRestored)
        : CallbackSystemEvent(aName)
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
    RTTI_PARENT(App::CallbackSystemEvent);
    RTTI_GETTER(restored);
    RTTI_GETTER(preGame);
});
