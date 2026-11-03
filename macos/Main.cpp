#include "MacDiag.hpp"
#include "MacExit.hpp"
#include "MacR13.hpp"
#include "MacR15.hpp"

#include "App/Application.hpp"
#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/MacHookStats.hpp"
#include "App/Project.hpp"
#include "Core/Facades/Runtime.hpp"

#include <cstdio>
#include <exception>

extern "C" void cw_autotest_log_registration(); // macos/MacAutotest.mm

namespace
{
bool g_initialized = false;

// The application: runtime paths, the address resolver, the hooking driver, logging and the services.
Core::UniquePtr<App::Application> g_app;

// An address inside this dylib. Core::ModuleImage turns it into the plugin path with dladdr.
int g_moduleAnchor = 0;
}

RED4EXT_C_EXPORT bool RED4EXT_CALL Main(RED4ext::v1::PluginHandle aHandle, RED4ext::v1::EMainReason aReason,
                                        const RED4ext::v1::Sdk* aSdk)
{
    try
    {
        switch (aReason)
        {
        case RED4ext::v1::EMainReason::Load:
        {
            if (g_initialized)
            {
                return true;
            }
            g_initialized = true;
            Mac::MarkPluginLoaded(aHandle, aSdk, "CW");
            cw_autotest_log_registration(); // test-only key injection, off unless CP2077_AUTOTEST=1 (macos/MacAutotest.mm)
            App::MacHookStats::MarkPluginLoad(); // Time zero for the hook timings (diagnostics).
            Mac::InstallCrashDiag();             // Fault report on stderr (always on).

            // R17 B3. The Application owns what used to be set up here: Core::Runtime (RuntimeProvider), the address
            // resolver, the hooking driver and logging (MacPlatformProvider). The resolver and the driver are
            // defaults before the first hook is installed below, as before.
            g_app = Core::MakeUnique<App::Application>(&g_moduleAnchor, aHandle, aSdk);
            g_app->Bootstrap();
            MAC_DIAG("[cw] Main load root=%s module=%s\n", Core::Runtime::GetRootDir().string().c_str(),
                     Core::Runtime::GetModuleDir().string().c_str());
            MAC_DIAG("[cw] application bootstrapped (address resolver and hooking driver set)\n");

            // R13. Resource/Load, Resource/PostLoad and Entity/Attach are hooked once, here, while the game
            // is still single-threaded. Their bodies wait for the CallbackSystem to exist before dispatching.
            const bool hooksOk = App::InstallMacCallbackHooks();
            MAC_DIAG_UNLESS(hooksOk, "[cw] callback hooks installed=%d\n", hooksOk ? 1 : 0);

            // The GameInstance hook, the GetGameInstance hook, the script validator layer and the opcode handlers are
            // installed by App::ScriptingService (it is registered in App::Application and bootstrapped above).
            break;
        }
        case RED4ext::v1::EMainReason::Unload:
        {
            g_initialized = false;
            if (g_app)
            {
                g_app->Shutdown();
                // R27: the plugins are unloaded from RED4ext's atexit handler, so the process is already leaving. The application owns tokens, handles and hook
                // state of the game; releasing them here goes through SDK relocations and the game's allocators while the game shuts down (quit crash in
                // ~SharedPtr -> UniversalRelocBase::Resolve). The hooks are off after Shutdown(); the memory is left to the process exit.
                (void)g_app.release();
            }
            MAC_DIAG("[cw] Main unload\n");
            Mac::ExitWhenAllPluginsUnloaded("CW");
            break;
        }
        }
        return true;
    }
    catch (const std::exception& ex)
    {
        std::fprintf(stderr, "[cw] Main exception %s\n", ex.what());
        return false;
    }
    catch (...)
    {
        std::fprintf(stderr, "[cw] Main exception\n");
        return false;
    }
}

RED4EXT_C_EXPORT void RED4EXT_CALL Query(RED4ext::v1::PluginInfo* aInfo)
{
    aInfo->name = App::Project::NameW;
    aInfo->author = App::Project::AuthorW;
    aInfo->version = RED4EXT_V1_SEMVER(App::Project::Version.major, App::Project::Version.minor, App::Project::Version.patch);
    aInfo->runtime = RED4EXT_V1_RUNTIME_VERSION_INDEPENDENT;
    aInfo->sdk = RED4EXT_V1_SDK_VERSION_1_0_0_COMPAT_0_5_0;
}

RED4EXT_C_EXPORT uint32_t RED4EXT_CALL Supports()
{
    return RED4EXT_API_VERSION_1_COMPAT_0;
}
