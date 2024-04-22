#pragma once

#include "Core/Facades/Container.hpp"
#include "App/Scripting/ScriptingService.hpp"

namespace App
{
struct ScriptableServiceContainer
{
    static inline Red::Handle<ScriptableService> Get(Red::CName aName)
    {
        return Core::Resolve<ScriptingService>()->GetScriptableService(aName);
    }
};
}

RTTI_DEFINE_CLASS(App::ScriptableServiceContainer, {
    RTTI_ABSTRACT();
    RTTI_METHOD(Get);
});
