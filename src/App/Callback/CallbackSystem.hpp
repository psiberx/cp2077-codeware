#pragma once

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
    Red::Handle<CallbackSystemHandler> RegisterStaticCallback(Red::CName aEventName, Red::CName aContext,
                                                              Red::CName aFunction, Red::Optional<bool> aSticky,
                                                              Red::CStackFrame* aFrame = nullptr);

    void UnregisterCallback(Red::CName aEventName, const Red::Handle<Red::IScriptable>& aContext,
                            Red::Optional<Red::CName> aFunction);
    void UnregisterStaticCallback(Red::CName aEventName, Red::CName aContext, Red::Optional<Red::CName> aFunction);

    bool RegisterEvent(Red::CName aEventName, Red::Optional<Red::CName> aEventType);
    void DispatchEvent(const Red::Handle<CallbackSystemEvent>& aEvent);
    void DispatchEventAs(Red::CName aEventName, const Red::Handle<CallbackSystemEvent>& aEvent);

    [[nodiscard]] bool IsRestored() const;
    [[nodiscard]] bool IsPreGame() const;

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

    RTTI_IMPL_TYPEINFO(App::CallbackSystem);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::CallbackSystem, {
    RTTI_METHOD(RegisterCallback);
    RTTI_METHOD(UnregisterCallback);
    RTTI_METHOD(RegisterStaticCallback);
    RTTI_METHOD(UnregisterStaticCallback);
    RTTI_METHOD(RegisterEvent);
    RTTI_METHOD(DispatchEvent);
    RTTI_METHOD(DispatchEventAs);
});
