#pragma once

#include "App/Callback/CallbackSystemEvent.hpp"

namespace App
{
struct CallbackSystemTarget : Red::IScriptable
{
    virtual bool Matches(const Red::Handle<CallbackSystemEvent>& aEvent) = 0;
    virtual bool Equals(const Red::Handle<CallbackSystemTarget>& aTarget) = 0;
    virtual bool Supports(Red::CName aEventType) = 0;

    RTTI_IMPL_TYPEINFO(App::CallbackSystemTarget);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::CallbackSystemTarget, {
    RTTI_ABSTRACT();
});
