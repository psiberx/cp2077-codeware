#include "Application.hpp"
#include "App/Facade.hpp"
#include "App/Entity/PersistencyService.hpp"
#include "App/Ink/WidgetBuildingService.hpp"
#include "App/Ink/WidgetSpawningService.hpp"
#include "App/Scripting/ScriptingService.hpp"
#include "Core/Foundation/RuntimeProvider.hpp"
#include "Red/Foundation/TypeInfoProvider.hpp"
#include "Vendor/MinHook/MinHookProvider.hpp"
#include "Vendor/RED4ext/RED4extProvider.hpp"
#include "Vendor/Spdlog/SpdlogProvider.hpp"

App::Application::Application(HMODULE aHandle, const RED4ext::Sdk* aSdk)
{
    Register<Core::RuntimeProvider>(aHandle)->SetBaseImagePathDepth(2);
    Register<Vendor::MinHookProvider>();
    Register<Vendor::SpdlogProvider>();
    Register<Red::TypeInfoProvider>();
    Register<App::ScriptingService>();
    Register<App::PersistencyService>();
    Register<App::WidgetBuildingService>();
    Register<App::WidgetSpawningService>();
}
