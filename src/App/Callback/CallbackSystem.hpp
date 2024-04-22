#pragma once

#include "CallbackSystemController.hpp"
#include "CallbackSystemEvent.hpp"
#include "CallbackSystemHandler.hpp"

namespace App
{
class CallbackSystem : public Red::IGameSystem
{
public:
    CallbackSystem();
    ~CallbackSystem() override;

    Red::Handle<CallbackSystemHandler> RegisterCallback(Red::CName aEvent, const Red::Handle<Red::IScriptable>& aTarget,
                                                        Red::CName aFunction, Red::Optional<bool> aSticky);
    Red::Handle<CallbackSystemHandler> RegisterStaticCallback(Red::CName aEvent, Red::CName aType, Red::CName aFunction,
                                                              Red::Optional<bool> aSticky);

    void UnregisterCallback(Red::CName aHandler, const Red::Handle<Red::IScriptable>& aContext,
                            Red::Optional<Red::CName> aFunction);
    void UnregisterStaticCallback(Red::CName aHandler, Red::CName aContext, Red::Optional<Red::CName> aFunction);

    void FireCallbacks(const Red::Handle<CallbackSystemEvent>& aEvent);

    [[nodiscard]] bool IsRestored() const;
    [[nodiscard]] bool IsPreGame() const;

    template<typename Event, typename... Args>
    inline void TriggerEvent(Red::CName aEventName, Args&&... aArgs)
    {
        Core::Vector<Red::Handle<CallbackSystemHandler>> callbacks;
        {
            std::shared_lock _(m_callbacksLock);
            const auto& callbacksIt = m_callbacksByEvent.find(aEventName);

            if (callbacksIt == m_callbacksByEvent.end())
                return;

            callbacks = callbacksIt.value();
        }

        const auto event = Red::MakeHandle<Event>(aEventName, std::forward<Args>(aArgs)...);

        for (const auto& callback : callbacks)
        {
            (*callback)(event);
        }
    }

    static void PassEvent(const Red::Handle<CallbackSystemEvent>& aEvent);

    template<typename Event, typename... Args>
    inline static void PassEvent(Red::CName aEventName, Args&&... aArgs)
    {
        if (s_self)
        {
            s_self->TriggerEvent<Event>(aEventName, std::forward<Args>(aArgs)...);
        }
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

    template<typename TController>
    inline void RegisterController()
    {
        auto controller = Core::MakeShared<TController>();

        for (const auto& event : controller->GetEvents())
        {
            m_eventControllers.emplace(event, controller);
        }
    }

    inline void ActivateEvent(Red::CName aEvent);
    inline void DeactivateEvent(Red::CName aEvent);

    bool m_restored;
    bool m_pregame;

    std::shared_mutex m_callbacksLock;
    Core::Map<Red::CName, Core::Vector<Red::Handle<CallbackSystemHandler>>> m_callbacksByEvent;
    Core::Map<Red::CName, Core::SharedPtr<CallbackSystemController>> m_eventControllers;

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
    RTTI_METHOD(FireCallbacks);
});
