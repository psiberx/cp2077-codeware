#pragma once

#if defined(__APPLE__)
#include <atomic>
#endif

#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/CallbackSystemEvent.hpp"
#include "App/Callback/CallbackSystemHandler.hpp"

namespace App
{
class CallbackSystem : public Red::IGameSystem
{
public:
    static constexpr auto SessionBeforeStartEventName = Red::CName("Session/BeforeStart");
    static constexpr auto SessionBeforeEndEventName = Red::CName("Session/BeforeEnd");
    static constexpr auto SessionEndEventName = Red::CName("Session/End");
    static constexpr auto SessionBeforeSaveEventName = Red::CName("Session/BeforeSave");
    static constexpr auto SessionAfterSaveEventName = Red::CName("Session/AfterSave");
    static constexpr auto SessionReadyEventName = Red::CName("Session/Ready");
    static constexpr auto SessionStartEventName = Red::CName("Session/Start");
    static constexpr auto SessionPauseEventName = Red::CName("Session/Pause");
    static constexpr auto SessionResumeEventName = Red::CName("Session/Resume");

    CallbackSystem();
    ~CallbackSystem() override;

    Red::Handle<CallbackSystemHandler> RegisterCallback(Red::CName aEvent,
                                                        const Red::Handle<Red::IScriptable>& aContext,
                                                        Red::CName aFunction, Red::Optional<bool> aSticky,
                                                        Red::CStackFrame* aFrame = nullptr);
    // Game 2.5's script declaration (the one mods compile against) takes the target as an object:
    // RegisterStaticCallback(eventName: CName, target: IScriptable, functionName: CName, opt sticky: Bool).
    // The static callback is bound to the target's class.
    Red::Handle<CallbackSystemHandler> RegisterStaticCallback(Red::CName aEventName,
                                                              const Red::Handle<Red::IScriptable>& aTarget,
                                                              Red::CName aFunction, Red::Optional<bool> aSticky,
                                                              Red::CStackFrame* aFrame = nullptr);

    void UnregisterCallback(Red::CName aEventName, const Red::Handle<Red::IScriptable>& aContext,
                            Red::Optional<Red::CName> aFunction);
    void UnregisterStaticCallback(Red::CName aEventName, Red::CName aContext, Red::Optional<Red::CName> aFunction);

    // Returns nothing on game 2.5, as the game's script declaration does.
    void RegisterEvent(Red::CName aEventName, Red::Optional<Red::CName> aEventType);
    bool RegisterEventImpl(Red::CName aEventName, Red::CName aEventType);
    void DispatchEvent(const Red::Handle<CallbackSystemEvent>& aEvent);
    void DispatchEventAs(Red::CName aEventName, const Red::Handle<CallbackSystemEvent>& aEvent);

    [[nodiscard]] bool IsRestored() const;
    [[nodiscard]] bool IsPreGame() const;

    // True when at least one callback is registered for the event. A cheap pre-check for hooks that would otherwise build
    // an event object (or copy game data) just to find that nobody listens.
    inline bool HasCallbacks(Red::CName aEventName)
    {
        std::shared_lock _(m_callbacksLock);
        const auto it = m_callbacksByEvent.find(aEventName);
        return it != m_callbacksByEvent.end() && !it.value().empty();
    }

    template<typename Event, typename... Args>
    inline bool DispatchNativeEvent(Red::CName aEventName, Args&&... aArgs)
    {
        Core::Vector<Red::Handle<CallbackSystemHandler>> callbacks(0);

        {
            std::shared_lock _(m_callbacksLock);
            const auto& callbacksIt = m_callbacksByEvent.find(aEventName);

            if (callbacksIt == m_callbacksByEvent.end())
                return false;

            callbacks = callbacksIt.value();
        }

        const auto event = Red::MakeHandle<Event>(aEventName, std::forward<Args>(aArgs)...);

        for (const auto& callback : callbacks)
        {
            (*callback)(event);
        }

        return true;
    }

    static Red::Handle<CallbackSystem>& Get();

#if defined(__APPLE__)
    // R13. True once Get() has built the singleton. The Mac resource and entity hooks are installed at
    // plugin load, before the CallbackSystem class is registered, and must not build the system early.
    static bool Exists()
    {
        return s_exists.load(std::memory_order_acquire);
    }

    // SELFTEST R18. Every event name the controllers declared, for the callback self-test.
    Core::Vector<Red::CName> MacSupportedEventNames()
    {
        Core::Vector<Red::CName> names;
        for (auto it = m_supportedEvents.begin(); it != m_supportedEvents.end(); ++it)
        {
            names.push_back(it.key());
        }
        return names;
    }

    // DIAG R14. Callbacks registered per event name (the deprecated names are mapped to the new ones:
    // Resource/Loaded is Resource/Load, Resource/Ready is Resource/PostLoad, Entity/Attached is Entity/AfterAttach).
    Core::Vector<std::pair<Red::CName, size_t>> MacCallbackCounts()
    {
        Core::Vector<std::pair<Red::CName, size_t>> counts;
        std::shared_lock _(m_callbacksLock);
        for (auto it = m_callbacksByEvent.begin(); it != m_callbacksByEvent.end(); ++it)
        {
            counts.emplace_back(it.key(), it.value().size());
        }
        return counts;
    }
#endif
protected:
    void OnWorldAttached(Red::world::RuntimeScene*) override;
    // void OnStreamingWorldLoaded(Red::world::RuntimeScene*, uint64_t aRestored, const Red::JobGroup&) override;
    void OnBeforeWorldDetach(Red::world::RuntimeScene* aScene) override;
    void OnWorldDetached(Red::world::RuntimeScene* aScene) override;
    void OnAfterWorldDetach() override;
    uint32_t OnBeforeGameSave(const Red::JobGroup& aJobGroup, void* a2) override;
    // void OnGameSave(void* aStream) override;
    void OnAfterGameSave() override;
    void OnGameLoad(const Red::JobGroup& aJobGroup, bool& aSuccess, void* aStream) override;
    void OnGamePrepared() override;
    bool OnGameRestored() override;
    void OnGamePaused() override;
    void OnGameResumed() override;

public:
    // The static callback bound to a class name (the body of RegisterStaticCallback, which takes the class from a target object).
    // macOS: the self-tests (macos/MacR13.cpp) register against their native class by name; no instance of it exists.
    Red::Handle<CallbackSystemHandler> RegisterStaticCallbackImpl(Red::CName aEventName, Red::CName aContext,
                                                                  Red::CName aFunction, Red::Optional<bool> aSticky,
                                                                  Red::CStackFrame* aFrame = nullptr);

protected:
    void MapEventName(Red::CName& aEventName);
    void ActivateEvent(Red::CName aEventName);
    void DeactivateEvent(Red::CName aEventName);
    void FireCallbacks(const Red::Handle<CallbackSystemEvent>& aEvent);

    template<typename TController>
    inline void RegisterController()
    {
        auto controller = Core::MakeShared<TController>();

        for (const auto& [eventName, eventObjectType] : controller->GetEvents())
        {
            m_eventControllers.emplace(eventName, controller);
            m_supportedEvents.emplace(eventName, eventObjectType);
        }

        for (const auto& [oldEventName, newEventName] : controller->GetMappings())
        {
            m_eventMappings.emplace(oldEventName, newEventName);
        }
    }

    bool m_restored;
    bool m_pregame;

    std::shared_mutex m_callbacksLock;
    Core::Map<Red::CName, Core::Vector<Red::Handle<CallbackSystemHandler>>> m_callbacksByEvent;
    Core::Map<Red::CName, Core::SharedPtr<CallbackSystemController>> m_eventControllers;
    Core::Map<Red::CName, Red::CName> m_supportedEvents;
    Core::Map<Red::CName, Red::CName> m_eventMappings;

    inline static Red::Handle<CallbackSystem> s_self;
#if defined(__APPLE__)
    inline static std::atomic<bool> s_exists{false};
#endif

    RTTI_IMPL_TYPEINFO(App::CallbackSystem);
    RTTI_IMPL_ALLOCATOR();
};
}

#if defined(__APPLE__)
namespace App
{
// R13. Attaches the three Mac callback hooks (Resource/Load, Resource/PostLoad, Entity/Attach) once, at
// plugin load. Needs the address resolver and the hooking driver to be set. Defined in CallbackSystem.cpp.
bool InstallMacCallbackHooks();
}
#endif

RTTI_DEFINE_CLASS(App::CallbackSystem, {
    RTTI_METHOD(RegisterCallback);
    RTTI_METHOD(UnregisterCallback);
    RTTI_METHOD(RegisterStaticCallback);
    RTTI_METHOD(UnregisterStaticCallback);
    RTTI_METHOD(RegisterEvent);
    RTTI_METHOD(DispatchEvent);
    RTTI_METHOD(DispatchEventAs);
});
