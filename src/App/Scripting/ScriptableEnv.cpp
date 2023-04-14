#include "ScriptableEnv.hpp"
#include "App/Scripting/ScriptingService.hpp"
#include "Core/Facades/Container.hpp"

Red::Handle<App::ScriptableEnv> App::ScriptableEnv::Get(Red::CName aName)
{
    return Core::Resolve<ScriptingService>()->GetEnvironment(Red::GetClass(aName));
}
