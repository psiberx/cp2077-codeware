#include "Application.hpp"
#include "App/Entity/PersistencyService.hpp"
#include "App/Ink/WidgetBuildingService.hpp"
#include "App/Ink/WidgetSpawningService.hpp"
#include "App/Scripting/ScriptingService.hpp"
#include "Core/Foundation/LocaleProvider.hpp"
#include "Core/Foundation/RuntimeProvider.hpp"
#include "Support/MinHook/MinHookProvider.hpp"
#include "Support/RedLib/RedLibProvider.hpp"
#include "Support/Spdlog/SpdlogProvider.hpp"

App::Application::Application(HMODULE aHandle, const RED4ext::Sdk* aSdk)
{
    Register<Core::LocaleProvider>();
    Register<Core::RuntimeProvider>(aHandle)->SetBaseImagePathDepth(2);

    Register<Support::MinHookProvider>();
    Register<Support::SpdlogProvider>();
    Register<Support::RedLibProvider>();

    Register<App::ScriptingService>();
    Register<App::PersistencyService>();
    Register<App::WidgetBuildingService>();
    Register<App::WidgetSpawningService>();
}
