#include "Application.hpp"
#include "App/Entity/PersistencyService.hpp"
#include "App/Environment.hpp"
#include "App/Localization/LocalizationService.hpp"
#include "App/Migration.hpp"
#include "App/Project.hpp"
#include "App/Quest/QuestPhaseRegistry.hpp"
#include "App/Scripting/ScriptingService.hpp"
#include "App/Shared/ResourcePathRegistry.hpp"
#include "App/UI/WidgetBuildingService.hpp"
#include "App/UI/WidgetInputService.hpp"
#include "App/UI/WidgetSpawningService.hpp"
#include "App/World/OpenWorldTracker.hpp"
#include "Core/Foundation/LocaleProvider.hpp"
#include "Core/Foundation/RuntimeProvider.hpp"
#include "Support/MinHook/MinHookProvider.hpp"
#include "Support/RED4ext/RED4extProvider.hpp"
#include "Support/RedLib/RedLibProvider.hpp"
#include "Support/Spdlog/SpdlogProvider.hpp"

App::Application::Application(HMODULE aHandle, const RED4ext::Sdk* aSdk)
{
    Register<Core::LocaleProvider>();
    Register<Core::RuntimeProvider>(aHandle)
        ->SetBaseImagePathDepth(2);

    Register<Support::MinHookProvider>();
    Register<Support::SpdlogProvider>()
        ->AppendTimestampToLogName()
        ->CreateRecentLogSymlink();
    Register<Support::RED4extProvider>(aHandle, aSdk)
        ->EnableAddressLibrary()
        ->RegisterScripts(Env::ScriptsDir());
    Register<Support::RedLibProvider>();

    Register<App::ScriptingService>(Env::PersistentDir());
    Register<App::LocalizationService>();
    Register<App::PersistencyService>();
    Register<App::ResourcePathRegistry>(Env::KnownHashesPath());
    Register<App::QuestPhaseRegistry>();
    Register<App::OpenWorldTracker>();
    Register<App::WidgetBuildingService>();
    Register<App::WidgetSpawningService>();
    Register<App::WidgetInputService>();
}

void App::Application::OnStarting()
{
    LogInfo("{} {} is initializing...", Project::Name, Project::Version.to_string());

    Migration::CleanUp(Env::LegacyScriptsDir());
}

void App::Application::OnStarted()
{
    LogInfo("{} is initialized.", Project::Name);
}
