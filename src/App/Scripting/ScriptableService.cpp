#include "ScriptableService.hpp"
#include "App/Scripting/ScriptingService.hpp"
#include "Core/Facades/Container.hpp"

Red::Handle<App::ScriptableService> App::ScriptableService::Get(Red::CName aName)
{
    return Core::Resolve<ScriptingService>()->GetScriptableService(Red::GetClass(aName));
}
