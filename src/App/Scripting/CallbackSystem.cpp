#include "CallbackSystem.hpp"
#include "App/Scripting/Events/EntityAssembleHook.hpp"
#include "App/Scripting/Events/EntityAttachHook.hpp"
#include "App/Scripting/Events/EntityDetachHook.hpp"
#include "App/Scripting/Events/EntityInitializeHook.hpp"
#include "App/Scripting/Events/EntityReassembleHook.hpp"
#include "App/Scripting/Events/EntityUninitializeHook.hpp"
#include "App/Scripting/Events/GameSessionEvent.hpp"
#include "App/Scripting/Events/PlayerSpawnedHook.hpp"
#include "Red/InkSystem.hpp"

App::CallbackSystem::CallbackSystem()
    : m_restored(false)
    , m_pregame(false)
{
    RegisterEvent<EntityAssembleHook>();
    RegisterEvent<EntityAttachHook>();
    RegisterEvent<EntityDetachHook>();
    RegisterEvent<EntityInitializeHook>();
    RegisterEvent<EntityReassembleHook>();
    RegisterEvent<EntityUninitializeHook>();
    RegisterEvent<PlayerSpawnedHook>();
}

App::CallbackSystem::~CallbackSystem()
{
    s_self.Reset();
}

void App::CallbackSystem::OnWorldAttached(Red::world::RuntimeScene*)
{
    {
        auto handler = Red::InkSystem::Get()->GetSystemRequestsHandler();
        Red::CallVirtual(handler.instance, "IsPreGame", m_pregame);
    }

    TriggerEvent<GameSessionEvent>("Session/BeforeStart", m_pregame, m_restored);
}

void App::CallbackSystem::OnStreamingWorldLoaded(Red::world::RuntimeScene*, uint64_t aRestored, const Red::JobGroup&)
{
    m_restored = aRestored;
}

void App::CallbackSystem::OnBeforeWorldDetach(RED4ext::world::RuntimeScene* aScene)
{
    TriggerEvent<GameSessionEvent>("Session/BeforeEnd", m_pregame, m_restored);
}

void App::CallbackSystem::OnWorldDetached(RED4ext::world::RuntimeScene* aScene)
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

        std::erase_if(callbackList, [](EventCallback& aCallback) -> bool {
            return !aCallback.IsSticky();
        });

        if (callbackList.empty())
        {
            UninitializeEvent(event);
        }
    }
}

uint32_t App::CallbackSystem::OnBeforeGameSave(const RED4ext::JobGroup& aJobGroup, void* a2)
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

void App::CallbackSystem::OnGamePrepared()
{
    TriggerEvent<GameSessionEvent>("Session/Start", m_pregame, m_restored);
}

bool App::CallbackSystem::OnGameRestored()
{
    TriggerEvent<GameSessionEvent>("Session/Ready", m_pregame, m_restored);

    return true;
}

void App::CallbackSystem::OnGamePaused()
{
    TriggerEvent<GameSessionEvent>("Session/Pause", m_pregame, m_restored);
}

void App::CallbackSystem::OnGameResumed()
{
    TriggerEvent<GameSessionEvent>("Session/Resume", m_pregame, m_restored);
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

bool App::CallbackSystem::IsRestored() const
{
    return m_restored;
}

bool App::CallbackSystem::IsPreGame() const
{
    return m_pregame;
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
