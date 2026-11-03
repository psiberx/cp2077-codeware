#include "Application.hpp"
#include "App/Environment.hpp"
#include "App/Project.hpp"
#include "Core/Foundation/RuntimeProvider.hpp"
#include "Support/RedLib/RedLibProvider.hpp"

#if defined(__APPLE__)
#include "App/Entity/PersistencyService.hpp"
#include "App/Localization/LocalizationService.hpp"
#include "App/Quest/QuestPhaseRegistry.hpp"
#include "App/Scripting/ScriptingService.hpp"
#include "App/Shared/ResourcePathRegistry.hpp"
#include "App/UI/WidgetBuildingService.hpp"
#include "App/UI/WidgetInputService.hpp"
#include "App/UI/WidgetSpawningService.hpp"
#include "App/World/OpenWorldTracker.hpp"
#include "MacProviders.hpp"
#else
#include "App/Entity/PersistencyService.hpp"
#include "App/Localization/LocalizationService.hpp"
#include "App/Migration.hpp"
#include "App/Quest/QuestPhaseRegistry.hpp"
#include "App/Scripting/ScriptingService.hpp"
#include "App/Shared/ResourcePathRegistry.hpp"
#include "App/UI/WidgetBuildingService.hpp"
#include "App/UI/WidgetInputService.hpp"
#include "App/UI/WidgetSpawningService.hpp"
#include "App/World/OpenWorldTracker.hpp"
#include "Core/Foundation/LocaleProvider.hpp"
#include "Support/MinHook/MinHookProvider.hpp"
#include "Support/RED4ext/RED4extProvider.hpp"
#include "Support/Spdlog/SpdlogProvider.hpp"
#endif

#if defined(__APPLE__)
App::Application::Application(void* aModule, RED4ext::v1::PluginHandle aPlugin, const RED4ext::v1::Sdk* aSdk)
{
    // No Core::LocaleProvider: it sets the C locale for the whole process, and the game on macOS does not need it
    // (UTF8StrLower and the other string natives pass their self-tests without it).
    // MAC-NOT-YET: no SpdlogProvider (logs go to stderr), no RED4extProvider::RegisterScripts (the script cache is built
    // offline by tools/build-cache.py) and no Migration::CleanUp (it deletes the legacy r6/scripts/Codeware folder).
    // Depth 3: <game>/Cyberpunk2077.app/Contents/MacOS/Cyberpunk2077 -> the game folder.
    Register<Core::RuntimeProvider>(aModule)
        ->SetBaseImagePathDepth(3);

    // Address resolver, hooking driver and logging (stand-in for MinHookProvider, SpdlogProvider and RED4extProvider).
    Register<Support::MacPlatformProvider>(aPlugin, aSdk);
    Register<Support::RedLibProvider>();

    // The services, in the order of the Windows constructor (all nine are on since R21).
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
#else
App::Application::Application(HMODULE aHandle, const RED4ext::v1::Sdk* aSdk)
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
#endif

void App::Application::OnStarting()
{
    LogInfo("{} {} is initializing...", Project::Name, Project::Version.to_string());

#if !defined(__APPLE__)
    Migration::CleanUp(Env::LegacyScriptsDir());
#endif
}

void App::Application::OnStarted()
{
    LogInfo("{} is initialized.", Project::Name);
}
