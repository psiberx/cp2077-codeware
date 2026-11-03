#pragma once

// R17 B3. The two game events that the Windows services get from their own hooks and that the macOS port drives from
// the plugin entry points instead:
//   natives registered   codeware_registerNatives, at script initialisation, before the scripts are linked
//                        (Windows: the RTTI register callbacks)
//   scripts loaded       codeware_postLoadScripts, first thing after LoadScripts returned: late type registration
//                        (Windows: the RTTI post-register callbacks)
//   services start       codeware_postLoadScripts, last thing, after the diagnostics: the scripted services run
//                        (Windows: HookAfter<ScriptBundle::Destruct>)
// A service (Core::Feature) subscribes from its OnBootstrap with Mac::Lifecycle::OnNativesRegistered(&Handler, name),
// OnScriptsLoaded and OnServicesStart. Handlers run in subscription order, which is the Application's registration
// order. A handler that throws is logged and the next one still runs.

#include <cstdio>
#include <exception>
#include <vector>

namespace Mac
{
class Lifecycle
{
public:
    using Callback = void (*)();

    static void OnNativesRegistered(Callback aCallback, const char* aName)
    {
        Add(s_natives, aCallback, aName);
    }

    static void OnScriptsLoaded(Callback aCallback, const char* aName)
    {
        Add(s_loaded, aCallback, aName);
    }

    static void OnServicesStart(Callback aCallback, const char* aName)
    {
        Add(s_start, aCallback, aName);
    }

    static void RunNativesRegistered()
    {
        Run(s_natives, "natives registered");
    }

    static void RunScriptsLoaded()
    {
        Run(s_loaded, "scripts loaded");
    }

    static void RunServicesStart()
    {
        Run(s_start, "services start");
    }

private:
    struct Entry
    {
        Callback callback;
        const char* name;
    };

    static void Add(std::vector<Entry>& aList, Callback aCallback, const char* aName)
    {
        if (aCallback)
        {
            aList.push_back({aCallback, aName});
        }
    }

    static void Run(const std::vector<Entry>& aList, const char* aEvent)
    {
        for (const auto& entry : aList)
        {
            try
            {
                entry.callback();
            }
            catch (const std::exception& ex)
            {
                std::fprintf(stderr, "[cw] lifecycle %s: %s threw %s\n", aEvent, entry.name, ex.what());
            }
            catch (...)
            {
                std::fprintf(stderr, "[cw] lifecycle %s: %s threw\n", aEvent, entry.name);
            }
        }
    }

    static inline std::vector<Entry> s_natives;
    static inline std::vector<Entry> s_loaded;
    static inline std::vector<Entry> s_start;
};
}
