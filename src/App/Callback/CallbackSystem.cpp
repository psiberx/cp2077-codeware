#include "CallbackSystem.hpp"
#include "App/Callback/Controllers/EntityAssembleHook.hpp"
#include "App/Callback/Controllers/EntityAttachHook.hpp"
#include "App/Callback/Controllers/EntityDetachHook.hpp"
#include "App/Callback/Controllers/EntityInitializeHook.hpp"
#include "App/Callback/Controllers/EntityReassembleHook.hpp"
#include "App/Callback/Controllers/EntityUninitializeHook.hpp"
#include "App/Callback/Controllers/PlayerSpawnedHook.hpp"
#include "App/Callback/Controllers/ResourceLoadHook.hpp"
#include "App/Callback/Controllers/ResourceReadyHook.hpp"
#include "App/Callback/Controllers/RawInputHook.hpp"
#include "App/Callback/Events/GameSessionEvent.hpp"
#include "App/Scripting/ScriptableService.hpp"
#include "Red/InkSystem.hpp"

App::CallbackSystem::CallbackSystem()
    : m_restored(false)
    , m_pregame(false)
{
    RegisterController<EntityAssembleHook>();
    RegisterController<EntityAttachHook>();
    RegisterController<EntityDetachHook>();
    RegisterController<EntityInitializeHook>();
    RegisterController<EntityReassembleHook>();
    RegisterController<EntityUninitializeHook>();
    RegisterController<PlayerSpawnedHook>();
    RegisterController<ResourceLoadHook>();
    RegisterController<ResourceReadyHook>();
    RegisterController<RawInputHook>();
}

App::CallbackSystem::~CallbackSystem()
{
    s_self.Reset();
}

void App::CallbackSystem::OnWorldAttached(Red::world::RuntimeScene*)
{
    {
        auto& handler = Red::InkSystem::Get()->GetSystemRequestsHandler();
        Red::CallVirtual(handler.instance, "IsPreGame", m_pregame);
    }

    TriggerEvent<GameSessionEvent>("Session/BeforeStart", m_pregame, m_restored);
}

// void App::CallbackSystem::OnStreamingWorldLoaded(Red::world::RuntimeScene*, uint64_t aRestored, const Red::JobGroup& aJobGroup)
// {
//     m_restored = aRestored;
// }

void App::CallbackSystem::OnBeforeWorldDetach(Red::world::RuntimeScene* aScene)
{
    TriggerEvent<GameSessionEvent>("Session/BeforeEnd", m_pregame, m_restored);
}

void App::CallbackSystem::OnWorldDetached(Red::world::RuntimeScene* aScene)
{
    TriggerEvent<GameSessionEvent>("Session/End", m_pregame, m_restored);
}

void App::CallbackSystem::OnAfterWorldDetach()
{
    m_restored = false;

    std::unique_lock _(m_callbacksLock);

    for (auto it = m_callbacksByEvent.begin(); it != m_callbacksByEvent.end(); ++it)
    {
        auto& event = it.key();
        auto& callbackList = it.value();

        std::erase_if(callbackList, [](Red::Handle<CallbackSystemHandler>& aCallback) -> bool {
            return !aCallback->IsSticky() || !aCallback->IsRegistered();
        });

        if (callbackList.empty())
        {
            DeactivateEvent(event);
        }
    }
}

uint32_t App::CallbackSystem::OnBeforeGameSave(const Red::JobGroup& aJobGroup, void* a2)
{
    TriggerEvent<GameSessionEvent>("Session/BeforeSave", m_pregame, m_restored);

    return 0;
}

// void App::CallbackSystem::OnGameSave(void* aStream)
// {
//     TriggerEvent<GameSessionEvent>("Session/Save", m_pregame, m_restored);
// }

void App::CallbackSystem::OnAfterGameSave()
{
    TriggerEvent<GameSessionEvent>("Session/AfterSave", m_pregame, m_restored);
}

void App::CallbackSystem::OnGameLoad(const Red::JobGroup& aJobGroup, bool& aSuccess, void* aStream)
{
    m_restored = true;
}

bool App::CallbackSystem::OnGameRestored()
{
    TriggerEvent<GameSessionEvent>("Session/Ready", m_pregame, m_restored);

    return true;
}

void App::CallbackSystem::OnGamePrepared()
{
    TriggerEvent<GameSessionEvent>("Session/Start", m_pregame, m_restored);
}

void App::CallbackSystem::OnGamePaused()
{
    TriggerEvent<GameSessionEvent>("Session/Pause", m_pregame, m_restored);
}

void App::CallbackSystem::OnGameResumed()
{
    TriggerEvent<GameSessionEvent>("Session/Resume", m_pregame, m_restored);
}

Red::Handle<App::CallbackSystemHandler> App::CallbackSystem::RegisterCallback(
    Red::CName aEventName, const Red::Handle<Red::IScriptable>& aContext, Red::CName aFunction,
    Red::Optional<bool> aSticky, Red::CStackFrame* aFrame)
{
    auto eventType = m_supportedEvents[aEventName];
    if (!eventType)
        return {};

    ActivateEvent(aEventName);

    auto handler = Red::MakeHandle<CallbackSystemHandler>(eventType, aContext, aFunction);
    if (aSticky || (aFrame && aFrame->context && Red::IsInstanceOf<ScriptableService>(aFrame->context)))
    {
        handler->SetLifetime(CallbackLifetime::Forever);
    }

    {
        std::unique_lock _(m_callbacksLock);
        m_callbacksByEvent[aEventName].push_back(handler);
    }

    return handler;
}

Red::Handle<App::CallbackSystemHandler> App::CallbackSystem::RegisterStaticCallback(
    Red::CName aEventName, Red::CName aContext, Red::CName aFunction,
    Red::Optional<bool> aSticky, Red::CStackFrame* aFrame)
{
    auto eventType = m_supportedEvents[aEventName];
    if (!eventType)
        return {};

    ActivateEvent(aEventName);

    auto handler = Red::MakeHandle<CallbackSystemHandler>(eventType, aContext, aFunction);
    if (aSticky || (aFrame && aFrame->context && Red::IsInstanceOf<ScriptableService>(aFrame->context)))
    {
        handler->SetLifetime(CallbackLifetime::Forever);
    }

    {
        std::unique_lock _(m_callbacksLock);
        m_callbacksByEvent[aEventName].push_back(handler);
    }

    return handler;
}

void App::CallbackSystem::UnregisterCallback(Red::CName aEvent, const Red::Handle<Red::IScriptable>& aContext,
                                             Red::Optional<Red::CName> aFunction)
{
    std::unique_lock _(m_callbacksLock);
    const auto& callbackListIt = m_callbacksByEvent.find(aEvent);

    if (callbackListIt == m_callbacksByEvent.end())
        return;

    auto& callbackList = callbackListIt.value();

    if (aFunction.IsEmpty())
    {
        std::erase_if(callbackList, [&aContext](Red::Handle<CallbackSystemHandler>& aHandler) -> bool {
            return aHandler->IsSameContext(aContext);
        });
    }
    else
    {
        std::erase_if(callbackList, [&aContext, &aFunction](Red::Handle<CallbackSystemHandler>& aHandler) -> bool {
            return aHandler->IsSameCallback(aContext, aFunction);
        });
    }

    if (callbackList.empty())
    {
        DeactivateEvent(aEvent);
    }
}

void App::CallbackSystem::UnregisterStaticCallback(Red::CName aEvent, Red::CName aContext,
                                                   Red::Optional<Red::CName> aFunction)
{
    std::unique_lock _(m_callbacksLock);
    const auto& callbackListIt = m_callbacksByEvent.find(aEvent);

    if (callbackListIt == m_callbacksByEvent.end())
        return;

    auto& callbackList = callbackListIt.value();

    if (aFunction.IsEmpty())
    {
        std::erase_if(callbackList, [&aContext](Red::Handle<CallbackSystemHandler>& aHandler) -> bool {
            return aHandler->IsSameContext(aContext);
        });
    }
    else
    {
        std::erase_if(callbackList, [&aContext, &aFunction](Red::Handle<CallbackSystemHandler>& aHandler) -> bool {
            return aHandler->IsSameCallback(aContext, aFunction);
        });
    }

    if (callbackList.empty())
    {
        DeactivateEvent(aEvent);
    }
}

void App::CallbackSystem::ActivateEvent(Red::CName aEvent)
{
    const auto& controllerIt = m_eventControllers.find(aEvent);
    if (controllerIt != m_eventControllers.end())
    {
        controllerIt.value()->ActivateEvent(aEvent);
    }
}

void App::CallbackSystem::DeactivateEvent(Red::CName aEvent)
{
    const auto& controllerIt = m_eventControllers.find(aEvent);
    if (controllerIt != m_eventControllers.end())
    {
        controllerIt.value()->DeactivateEvent(aEvent);
    }
}

void App::CallbackSystem::FireCallbacks(const Red::Handle<CallbackSystemEvent>& aEvent)
{
    Core::Vector<Red::Handle<CallbackSystemHandler>> callbacks;
    {
        std::shared_lock _(m_callbacksLock);
        const auto& callbacksIt = m_callbacksByEvent.find(aEvent->eventName);

        if (callbacksIt == m_callbacksByEvent.end())
            return;

        callbacks = callbacksIt.value();
    }

    for (const auto& callback : callbacks)
    {
        (*callback)(aEvent);
    }
}

bool App::CallbackSystem::IsRestored() const
{
    return m_restored;
}

bool App::CallbackSystem::IsPreGame() const
{
    return m_pregame;
}

void App::CallbackSystem::PassEvent(const Red::Handle<CallbackSystemEvent>& aEvent)
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
