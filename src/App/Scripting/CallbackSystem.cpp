#include "CallbackSystem.hpp"
#include "App/Scripting/EventControllers/EntityAssembleHook.hpp"
#include "App/Scripting/EventControllers/EntityAttachHook.hpp"
#include "App/Scripting/EventControllers/EntityDetachHook.hpp"
#include "App/Scripting/EventControllers/EntityInitializeHook.hpp"
#include "App/Scripting/EventControllers/EntityReassembleHook.hpp"
#include "App/Scripting/EventControllers/EntityUninitializeHook.hpp"

App::CallbackSystem::CallbackSystem()
{
    RegisterEvent<EntityAssembleHook>();
    RegisterEvent<EntityAttachHook>();
    RegisterEvent<EntityDetachHook>();
    RegisterEvent<EntityInitializeHook>();
    RegisterEvent<EntityReassembleHook>();
    RegisterEvent<EntityUninitializeHook>();
}

App::CallbackSystem::~CallbackSystem()
{
    s_self.Reset();
}

void App::CallbackSystem::OnWorldAttached(Red::world::RuntimeScene*)
{
}

void App::CallbackSystem::OnAfterWorldDetach()
{
    std::unique_lock _(m_callbacksLock);

    for (auto it = m_callbacksByEvent.begin(); it != m_callbacksByEvent.end(); ++it)
    {
        auto& event = it.key();
        auto& callbackList = it.value();

        std::erase_if(callbackList, [](EventCallback& aCallback) -> bool {
            return !aCallback.IsSticky();
        });

        if (callbackList.empty())
        {
            UninitializeEvent(event);
        }
    }
}

void App::CallbackSystem::RegisterCallback(Red::CName aEvent, const Red::Handle<Red::IScriptable>& aTarget,
                                           Red::CName aFunction, Red::Optional<bool> aSticky)
{
    std::unique_lock _(m_callbacksLock);
    m_callbacksByEvent[aEvent].emplace_back(aTarget, aFunction, aSticky);

    InitializeEvent(aEvent);
}

void App::CallbackSystem::UnregisterCallback(Red::CName aEvent, const Red::Handle<Red::IScriptable>& aTarget,
                                             Red::Optional<Red::CName> aFunction)
{
    std::unique_lock _(m_callbacksLock);
    const auto& callbackListIt = m_callbacksByEvent.find(aEvent);

    if (callbackListIt != m_callbacksByEvent.end())
    {
        auto& callbackList = callbackListIt.value();

        std::erase_if(callbackList, [&aTarget, &aFunction](EventCallback& aCallback) -> bool {
            return aCallback.object.instance == aTarget && (aFunction.IsEmpty() || aCallback.function == aFunction);
        });

        if (callbackList.empty())
        {
            UninitializeEvent(aEvent);
        }
    }
}

void App::CallbackSystem::RegisterStaticCallback(Red::CName aEvent, Red::CName aType, Red::CName aFunction,
                                                 Red::Optional<bool> aSticky)
{
    std::unique_lock _(m_callbacksLock);
    m_callbacksByEvent[aEvent].emplace_back(aType, aFunction, aSticky);

    InitializeEvent(aEvent);
}

void App::CallbackSystem::UnregisterStaticCallback(Red::CName aEvent, Red::CName aType,
                                                   Red::Optional<Red::CName> aFunction)
{
    std::unique_lock _(m_callbacksLock);
    const auto& callbackListIt = m_callbacksByEvent.find(aEvent);

    if (callbackListIt != m_callbacksByEvent.end())
    {
        auto& callbackList = callbackListIt.value();

        std::erase_if(callbackList, [&aType, &aFunction](EventCallback& aCallback) -> bool {
            return aCallback.type == aType && (aFunction.IsEmpty() || aCallback.function == aFunction);
        });

        if (callbackList.empty())
        {
            UninitializeEvent(aEvent);
        }
    }
}

void App::CallbackSystem::InitializeEvent(Red::CName aEvent)
{
    const auto& controllerIt = m_eventControllers.find(aEvent);
    if (controllerIt != m_eventControllers.end())
    {
        controllerIt.value()->Initialize();
    }
}

void App::CallbackSystem::UninitializeEvent(Red::CName aEvent)
{
    const auto& controllerIt = m_eventControllers.find(aEvent);
    if (controllerIt != m_eventControllers.end())
    {
        controllerIt.value()->Uninitialize();
    }
}

void App::CallbackSystem::FireCallbacks(const Red::Handle<NamedEvent>& aEvent)
{
    Core::Vector<EventCallback> callbacks;
    {
        std::shared_lock _(m_callbacksLock);
        const auto& callbacksIt = m_callbacksByEvent.find(aEvent->eventName);

        if (callbacksIt == m_callbacksByEvent.end())
            return;

        callbacks = callbacksIt.value();
    }

    for (const auto& callback : callbacks)
    {
        callback(aEvent);
    }
}

void App::CallbackSystem::PassEvent(const Red::Handle<NamedEvent>& aEvent)
{
    if (s_self)
    {
        s_self->FireCallbacks(aEvent);
    }
}

Red::Handle<App::CallbackSystem>& App::CallbackSystem::Get()
{
    if (!s_self)
    {
        s_self = Red::MakeHandle<CallbackSystem>();
    }

    return s_self;
}
