#pragma once

#include "EventCallback.hpp"
#include "EventController.hpp"

namespace App
{
class CallbackSystem : public Red::IGameSystem
{
public:
    CallbackSystem();
    ~CallbackSystem() override;

    void RegisterCallback(Red::CName aEvent, const Red::Handle<Red::IScriptable>& aTarget, Red::CName aFunction,
                          Red::Optional<bool> aPermanent);
    void UnregisterCallback(Red::CName aEvent, const Red::Handle<Red::IScriptable>& aTarget,
                            Red::Optional<Red::CName> aFunction);

    void RegisterStaticCallback(Red::CName aEvent, Red::CName aType, Red::CName aFunction,
                                Red::Optional<bool> aPermanent);
    void UnregisterStaticCallback(Red::CName aEvent, Red::CName aType, Red::Optional<Red::CName> aFunction);

    //void TriggerEvent(Red::CName aEvent, Red::Optional<Red::DynArray<Red::Variant>>& aArgs);

    template<typename TController>
    inline void RegisterEvent()
    {
        auto controller = Core::MakeShared<TController>();

        for (const auto& event : controller->GetEvents())
        {
            m_eventControllers.emplace(event, controller);
        }
    }

    template<typename... Args>
    inline static void PassEvent(Red::CName aEvent, Args&&... aArgs)
    {
        if (s_self)
        {
            s_self->TriggerEvent(aEvent, std::forward<Args>(aArgs)...);
        }
    }

protected:
    void OnWorldAttached(Red::world::RuntimeScene*) override;
    void OnAfterWorldDetach() override;

    inline void InitializeEvent(Red::CName aEvent);
    inline void UninitializeEvent(Red::CName aEvent);

    template<typename... Args>
    inline void TriggerEvent(Red::CName aEvent, Args&&... aArgs)
    {
        std::shared_lock _(m_callbacksLock);
        const auto& callbackListIt = m_callbacksByEvent.find(aEvent);

        if (callbackListIt != m_callbacksByEvent.end())
        {
            for (const auto& callback : callbackListIt.value())
            {
                callback(aEvent, std::forward<Args>(aArgs)...);
            }
        }
    }

    std::shared_mutex m_callbacksLock;
    Core::Map<Red::CName, Core::Vector<EventCallback>> m_callbacksByEvent;
    Core::Map<Red::CName, Core::SharedPtr<EventController>> m_eventControllers;

    inline static CallbackSystem* s_self;

    RTTI_IMPL_TYPEINFO(App::CallbackSystem);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::CallbackSystem, {
    RTTI_METHOD(RegisterCallback);
    RTTI_METHOD(UnregisterCallback);
    RTTI_METHOD(RegisterStaticCallback);
    RTTI_METHOD(UnregisterStaticCallback);
});
