#pragma once

#include "EventCallback.hpp"
#include "EventController.hpp"
#include "EventObject.hpp"

namespace App
{
class CallbackSystem : public Red::IGameSystem
{
public:
    CallbackSystem();
    ~CallbackSystem() override;

    void RegisterCallback(Red::CName aEvent, const Red::Handle<Red::IScriptable>& aTarget, Red::CName aFunction,
                          Red::Optional<bool> aSticky);
    void UnregisterCallback(Red::CName aEvent, const Red::Handle<Red::IScriptable>& aTarget,
                            Red::Optional<Red::CName> aFunction);

    void RegisterStaticCallback(Red::CName aEvent, Red::CName aType, Red::CName aFunction,
                                Red::Optional<bool> aSticky);
    void UnregisterStaticCallback(Red::CName aEvent, Red::CName aType, Red::Optional<Red::CName> aFunction);

    void FireCallbacks(const Red::Handle<NamedEvent>& aEvent);

    template<typename TController>
    inline void RegisterEvent()
    {
        auto controller = Core::MakeShared<TController>();

        for (const auto& event : controller->GetEvents())
        {
            m_eventControllers.emplace(event, controller);
        }
    }

    static void PassEvent(const Red::Handle<NamedEvent>& aEvent);

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
    void OnAfterWorldDetach() override;

    inline void InitializeEvent(Red::CName aEvent);
    inline void UninitializeEvent(Red::CName aEvent);

    template<typename Event, typename... Args>
    inline void TriggerEvent(Red::CName aEventName, Args&&... aArgs)
    {
        Core::Vector<EventCallback> callbacks;
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
            callback(event);
        }
    }

    std::shared_mutex m_callbacksLock;
    Core::Map<Red::CName, Core::Vector<EventCallback>> m_callbacksByEvent;
    Core::Map<Red::CName, Core::SharedPtr<EventController>> m_eventControllers;

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
