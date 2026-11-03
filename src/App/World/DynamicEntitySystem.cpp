#include "DynamicEntitySystem.hpp"
#include "Red/RuntimeScene.hpp"
#include "Red/TagSystem.hpp"
#include "Red/TweakDB.hpp"
#if defined(__APPLE__)
#include "MacEngine.hpp"
#include "MacR21.hpp"
#include "MacDiag.hpp"
#endif

namespace
{
constexpr auto SystemPersistentID = Red::PersistentID(Red::GetTypeName<App::DynamicEntitySystem>());
}

void App::DynamicEntitySystem::OnWorldAttached(Red::worldRuntimeScene*)
{
#if defined(__APPLE__)
    if (!Red::MacSystemEnabled("DynamicEntitySystem"))
    {
        Red::MacSystemOff("DynamicEntitySystem", "switched off with CODEWARE_MAC_SYSTEMS_OFF");
        return;
    }
    if (!Red::GetRuntimeSystem<Red::worldRuntimeEntityRegistry>())
    {
        Red::MacSystemOff("DynamicEntitySystem", "the runtime entity registry is not reachable");
        return;
    }
#endif
    m_persistencySystem = Red::GetGameSystem<Red::IPersistencySystem>();
    m_entityIDSystem = Red::GetGameSystem<Red::IDynamicEntityIDSystem>();
    m_entityStubSystem = Red::GetGameSystem<Red::IEntityStubSystem>();
#if defined(__APPLE__)
    // R21: the redTagSystem inside GameTagSystem is at +0x48 on Mac too (the Mac callers of TagSystem_AssignTag add 0x48 to the game
    // system); the pointer is only formed when the game system exists.
    {
        auto* gameTagSystem = Red::GetGameSystem<Red::GameTagSystem>();
        m_entityTagSystem = gameTagSystem ? Raw::GameTagSystem::TagSystem::Ptr(gameTagSystem) : nullptr;
    }
#else
    m_entityTagSystem = Raw::GameTagSystem::TagSystem::Ptr(Red::GetGameSystem<Red::GameTagSystem>());
#endif
    m_entityRegistry = Red::GetRuntimeSystem<Red::worldRuntimeEntityRegistry>();
    m_populationSystem = Red::GetGameSystem<Red::IPopulationSystem>();
    m_spawnEventBroadcaster = Red::GetGameSystem<Red::IEntitySpawnerEventsBroadcaster>();
    m_persistentStateType = Red::GetClass<DynamicEntitySystemPS>();
    m_ready = true;
#if defined(__APPLE__)
    // SELFTEST R18. The systems it needs are all reachable at the world attach.
    MAC_DIAG(
                 "[cw] R18 DynamicEntitySystem ready persistency=%p idSystem=%p stubSystem=%p tagSystem=%p registry=%p "
                 "population=%p spawnBroadcaster=%p psType=%p\n",
                 static_cast<void*>(m_persistencySystem), static_cast<void*>(m_entityIDSystem),
                 static_cast<void*>(m_entityStubSystem), static_cast<void*>(m_entityTagSystem),
                 static_cast<void*>(m_entityRegistry), static_cast<void*>(m_populationSystem),
                 static_cast<void*>(m_spawnEventBroadcaster), static_cast<void*>(m_persistentStateType));
    Mac::R18Check(m_persistencySystem && m_entityIDSystem && m_entityStubSystem && m_entityRegistry,
                  "DynamicEntitySystem finds the persistency, ID and stub systems and the registry");
    // SELFTEST R21. The tag system at GameTagSystem + 0x48 (confirmed by the Mac callers of AssignTag): assign and unassign a
    // test tag on an entity id no entity has.
    Mac::R21TagRoundTrip(m_entityTagSystem);
#endif
}

void App::DynamicEntitySystem::OnStreamingWorldLoaded(Red::worldRuntimeScene*, uint64_t aRestored,
                                                      const Red::JobGroup&)
{
#if defined(__APPLE__)
    // MAC-NOT-YET: RegisterListener (a RED4ext callback object the game invokes on every entity spawn) is not verified against
    // the Mac game beyond its return (r18g); the game calls our callback in game only (INGAME_TESTS.md). The guards keep a
    // missing game system from becoming a null call.
    if (!m_ready || !m_spawnEventBroadcaster || !m_persistencySystem || !m_persistentStateType)
        return;
#endif
    m_restored = aRestored;

    m_spawnEventListenerID = m_spawnEventBroadcaster->RegisterListener(
        {this, &DynamicEntitySystem::OnEntitySpawnerEvent}, "");

#if defined(__APPLE__)
    // R21: IPersistencySystem::GetPersistentState returns the Handle through x8 on Mac (the SDK declaration has the Apple form), the
    // adapter r18g lacked. Guarded against a game system or state that did not come back.
    m_persistentState = Red::Cast<DynamicEntitySystemPS>(
        m_persistencySystem->GetPersistentState(SystemPersistentID, m_persistentStateType, true));
    if (!m_persistentState)
        return;
    m_persistentState->RestoreAfterLoading();
#else
    m_persistencySystem->GetPersistentState(m_persistentState, SystemPersistentID, m_persistentStateType, true);
    m_persistentState->RestoreAfterLoading();
#endif

    for (const auto& entityState : m_persistentState->GetEntityStates())
    {
        if (entityState->deleted)
            continue;

        RestoreEntityState(entityState);

        if (entityState->entitySpec->persistSpawn && entityState->entitySpec->active)
        {
            SpawnFromEntityState(entityState);
        }
    }

    m_persistentState->Clear();
}

uint32_t App::DynamicEntitySystem::OnBeforeGameSave(const Red::JobGroup& aJobGroup, void* a2)
{
#if defined(__APPLE__)
    if (!m_ready || !m_persistentState)
        return 0;
#endif
    std::scoped_lock _(m_entityStatesLock, m_entityTagsLock);

    for (const auto& entityState : m_entityStates)
    {
        if (entityState->deleted)
            continue;

        if (entityState->entitySpec->persistState || entityState->entitySpec->persistSpawn)
        {
            m_persistentState->AddEntityState(entityState);
        }
    }

    m_persistentState->PrepareForSaving();

    return 0;
}

void App::DynamicEntitySystem::OnAfterGameSave()
{
#if defined(__APPLE__)
    if (!m_ready || !m_persistentState)
        return;
#endif
    m_persistentState->Clear();
}

void App::DynamicEntitySystem::OnBeforeWorldDetach(Red::worldRuntimeScene* aScene)
{
#if defined(__APPLE__)
    if (!m_spawnEventBroadcaster)
        return;
#endif
    if (m_spawnEventListenerID)
    {
        m_spawnEventBroadcaster->UnregisterListener(m_spawnEventListenerID);
        m_spawnEventListenerID = {};
    }
}

void App::DynamicEntitySystem::OnAfterWorldDetach()
{
    m_ready = false;
    m_restored = false;
    m_persistentState.Reset();

#if defined(__APPLE__)
    // MAC-NOT-YET: an entity still spawned at the world detach keeps its stub in its state. Codeware must not free it: the Mac game
    // destroys stubs with its own destructor 0x101FD2C40 and frees them into PoolGMPL_PS (every call site, DeleteStub 0x101FD7734
    // included), and the stub system may still track the stub by its ID (FindStub), so a free here could be a double free. R33
    // released them here; since R34 the SDK gives EntityStub no allocator on the Mac and the state's holder (MacEntityStubRef) never
    // frees, so this hand-off only makes the count visible. A few 0x50-byte stubs leak per session end. The states are copied first
    // so that each state's own lock is not taken under m_entityStatesLock (OnEntitySpawnerEvent takes them in the other order).
    {
        Core::Vector<DynamicEntityStatePtr> states;
        {
            std::shared_lock _(m_entityStatesLock);
            states = m_entityStates;
        }
        uint32_t leaked = 0;
        for (const auto& entityState : states)
        {
            if (auto entityStub = entityState->ExtractStub())
            {
                (void)entityStub.Release();
                ++leaked;
            }
        }
        if (leaked)
        {
            MAC_DIAG("[cw] DynamicEntitySystem world detach: %u stub(s) of entities still spawned left to the game (not freed)\n",
                     leaked);
        }
    }
#endif

    {
        std::scoped_lock _(m_entityStatesLock, m_entityTagsLock);
        m_entityStates.clear();
        m_entityStateByID.clear();
        m_entityIDsByTag.clear();
    }

    {
        std::unique_lock _(m_listenersLock);
        m_listenersByTag.clear();
    }
}

void App::DynamicEntitySystem::OnEntitySpawnerEvent(Red::gameEntitySpawnerEventType aType, Red::EntityID aEntityID,
                                                    Red::EntityID, Red::EntityStub* aStub)
{
    if (aType == Red::gameEntitySpawnerEventType::Spawn)
    {
        if (auto entity = GetEntity(aEntityID))
        {
            if (const auto& gameObject = Red::Cast<Red::GameObject>(entity))
            {
                gameObject->tags.Add(GetTags(aEntityID));
            }
            else
            {
                Raw::RuntimeEntityRegistry::RegisterEntity(m_entityRegistry, entity);
            }
        }
    }

    ProcessListeners(aEntityID, aType);

    if (aType == Red::gameEntitySpawnerEventType::Despawn)
    {
        auto entityState = FindEntityState(aEntityID);
        if (entityState)
        {
            std::shared_lock _(entityState->entityLock);

            if (entityState->deleted)
            {
                RemoveEntityState(entityState);
            }
        }
    }
}

bool App::DynamicEntitySystem::IsReady() const
{
    return m_ready;
}

bool App::DynamicEntitySystem::IsRestored() const
{
    return m_restored;
}

Red::EntityID App::DynamicEntitySystem::CreateEntity(const DynamicEntitySpecPtr& aEntitySpec)
{
    if (!m_ready)
        return {};

    if (!ValidateEntitySpec(aEntitySpec))
        return {};

    auto entityState = CreateEntityState(aEntitySpec);
    if (!entityState)
        return {};

    if (aEntitySpec->active)
    {
        SpawnFromEntityState(entityState);
    }

    return entityState->entityID;
}

bool App::DynamicEntitySystem::DeleteEntity(Red::EntityID aEntityID)
{
    if (!m_ready)
        return false;

    auto entityState = FindEntityState(aEntityID);
    if (!entityState)
        return false;

    {
        std::unique_lock _(entityState->entityLock);

        if (entityState->deleted)
            return false;

        entityState->deleted = true;
    }

    if (!DespawnFromEntityState(entityState))
    {
        RemoveEntityState(entityState);
    }

    return true;
}

bool App::DynamicEntitySystem::EnableEntity(Red::EntityID aEntityID)
{
    if (!m_ready)
        return false;

    auto entityState = FindEntityState(aEntityID);
    if (!entityState)
        return false;

    {
        std::unique_lock _(entityState->entityLock);

        if (entityState->entitySpec->active)
            return false;

        entityState->entitySpec->active = true;
    }

    return SpawnFromEntityState(entityState);
}

bool App::DynamicEntitySystem::DisableEntity(Red::EntityID aEntityID)
{
    if (!m_ready)
        return false;

    auto entityState = FindEntityState(aEntityID);
    if (!entityState)
        return false;

    {
        std::unique_lock _(entityState->entityLock);

        if (!entityState->entitySpec->active)
            return false;

        entityState->entitySpec->active = false;
    }

    return DespawnFromEntityState(entityState);
}

bool App::DynamicEntitySystem::SpawnFromEntityState(const App::DynamicEntityStatePtr& aEntityState)
{
    Red::EntityStubCreateRequest request{aEntityState->entityID,
                                         aEntityState->entitySpec->position,
                                         aEntityState->entitySpec->orientation,
                                         aEntityState->entitySpec->recordID};

#if defined(__APPLE__)
    // macOS: CreateStub returns the token through x8 (the SDK declares the Apple form); the callback goes as an rvalue.
    auto token = m_entityStubSystem->CreateStub(request, Red::EntityStubCallback([this, aEntityState](Red::EntityStubTokenPtr& aToken) {
#else
    auto token = m_entityStubSystem->CreateStub(request, [this, aEntityState](Red::EntityStubTokenPtr& aToken) {
#endif
        if (aToken->status != Red::EntityStubStatus::Created)
        {
            RemoveEntityState(aEntityState);
            return;
        }

        aEntityState->AcquireStub(aToken);

        Red::PopulationEntityRegisterRequest request{};
        request.entityID = aEntityState->entityID;
        request.spawnInView = aEntityState->entitySpec->spawnInView;
        request.alwaysSpawned = aEntityState->entitySpec->alwaysSpawned;

        if (aEntityState->entitySpec->appearanceName)
        {
            request.appearanceName = aEntityState->entitySpec->appearanceName;
            request.prefetchAppearance = true;
        }

        m_populationSystem->RegisterEntity(request);
#if defined(__APPLE__)
    }));
#else
    });
#endif

    return true;
}

bool App::DynamicEntitySystem::DespawnFromEntityState(const App::DynamicEntityStatePtr& aEntityState)
{
    if (auto entityStub = aEntityState->ExtractStub())
    {
        m_populationSystem->RemoveEntity(aEntityState->entityID, 0);
#if defined(__APPLE__)
        // The macOS SDK declares DeleteStub(EntityStub*&) and the system takes the stub over: hand the pointer over.
        auto* stub = entityStub.Release();
        m_entityStubSystem->DeleteStub(stub);
#else
        m_entityStubSystem->DeleteStub(std::move(entityStub));
#endif

        return true;
    }

    return false;
}

App::DynamicEntityStatePtr App::DynamicEntitySystem::CreateEntityState(const App::DynamicEntitySpecPtr& aEntitySpec)
{
    auto entityID = aEntitySpec->persistState ? m_entityIDSystem->GetNextPersistableID()
                                              : m_entityIDSystem->GetNextTransientID();
    if (!entityID.IsDefined())
        return {};

    auto entityState = Red::MakeHandle<DynamicEntityState>(entityID, aEntitySpec);

    if (aEntitySpec->IsTemplate())
    {
        aEntitySpec->recordID = ConvertTemplateToRecord(aEntitySpec->templatePath);
    }

    AddEntityState(entityState);

    return entityState;
}

void App::DynamicEntitySystem::RestoreEntityState(const App::DynamicEntityStatePtr& aEntityState)
{
    auto& entitySpec = aEntityState->entitySpec;

    if (entitySpec->templateHash && entitySpec->recordID.name.length <= 1)
    {
        entitySpec->recordID = ConvertTemplateToRecord(entitySpec->templatePath);
    }

    if (!aEntityState->entitySpec->persistState)
    {
        m_persistencySystem->RemoveDynamicEntityState(aEntityState->entityID);

        aEntityState->entityID = m_entityIDSystem->GetNextTransientID();
    }

    AddEntityState(aEntityState);
}

void App::DynamicEntitySystem::AddEntityState(const App::DynamicEntityStatePtr& aEntityState)
{
    std::scoped_lock _(m_entityStatesLock, m_entityTagsLock);

    m_entityStates.emplace_back(aEntityState);
    m_entityStateByID.insert({aEntityState->entityID, aEntityState});

    for (const auto& tag : aEntityState->entitySpec->tags)
    {
        m_entityIDsByTag[tag].insert(aEntityState->entityID);
    }
}

void App::DynamicEntitySystem::RemoveEntityState(const App::DynamicEntityStatePtr& aEntityState)
{
    std::scoped_lock _(m_entityStatesLock, m_entityTagsLock);

    for (const auto& tag : aEntityState->entitySpec->tags)
    {
        m_entityIDsByTag[tag].erase(aEntityState->entityID);
    }

    m_entityStateByID.erase(aEntityState->entityID);
    std::erase(m_entityStates, aEntityState);

    m_persistencySystem->RemoveDynamicEntityState(aEntityState->entityID);
}

App::DynamicEntityStatePtr App::DynamicEntitySystem::FindEntityState(Red::EntityID aEntityID)
{
    std::shared_lock _(m_entityStatesLock);

    auto entityStateIt = m_entityStateByID.find(aEntityID);

    if (entityStateIt == m_entityStateByID.end())
        return {};

    return entityStateIt.value();
}

bool App::DynamicEntitySystem::IsManaged(Red::EntityID aEntityID)
{
    if (!m_ready)
        return false;

    std::shared_lock _(m_entityStatesLock);

    return m_entityStateByID.contains(aEntityID);
}

bool App::DynamicEntitySystem::IsTagged(Red::EntityID aEntityID, Red::CName aTag)
{
    if (!m_ready)
        return false;

    std::shared_lock _(m_entityTagsLock);

    const auto taggedIt = m_entityIDsByTag.find(aTag);
    if (taggedIt == m_entityIDsByTag.end())
        return false;

    return taggedIt.value().contains(aEntityID);
}

bool App::DynamicEntitySystem::IsSpawned(Red::EntityID aEntityID)
{
    if (!m_ready)
        return false;

    return GetEntity(aEntityID);
}

bool App::DynamicEntitySystem::IsSpawning(Red::EntityID aEntityID)
{
    if (!m_ready)
        return false;

    return m_populationSystem->IsSpawning(aEntityID);
}

Red::Handle<Red::Entity> App::DynamicEntitySystem::GetEntity(Red::EntityID aEntityID)
{
    if (!m_ready)
        return {};

    return m_populationSystem->FindEntity(aEntityID);
}

Red::DynArray<Red::CName> App::DynamicEntitySystem::GetTags(Red::EntityID aEntityID)
{
    if (!m_ready)
        return {};

    auto entityState = FindEntityState(aEntityID);
    if (!entityState)
        return {};

    std::shared_lock _(m_entityTagsLock);

    return entityState->entitySpec->tags;
}

bool App::DynamicEntitySystem::AssignTag(Red::EntityID aEntityID, Red::CName aTag)
{
    if (!m_ready)
        return false;

    auto entityState = FindEntityState(aEntityID);
    if (!entityState)
        return false;

    std::unique_lock _(m_entityTagsLock);

    auto& tagged = m_entityIDsByTag[aTag];

    if (!tagged.contains(aEntityID))
    {
        tagged.insert(aEntityID);

        entityState->entitySpec->tags.PushBack(aTag);

        if (auto entity = GetEntity(aEntityID))
        {
            if (const auto& gameObject = Red::Cast<Red::GameObject>(entity))
            {
                gameObject->tags.Add(aTag);
                Raw::TagSystem::AssignTag(m_entityTagSystem, aEntityID, aTag);
            }
        }
    }

    return true;
}

bool App::DynamicEntitySystem::UnassignTag(Red::EntityID aEntityID, Red::CName aTag)
{
    if (!m_ready)
        return false;

    auto entityState = FindEntityState(aEntityID);
    if (!entityState)
        return false;

    std::unique_lock _(m_entityTagsLock);

    auto& tagged = m_entityIDsByTag[aTag];

    if (tagged.contains(aEntityID))
    {
        tagged.erase(aEntityID);

        entityState->entitySpec->tags.Remove(aTag);

        if (auto entity = GetEntity(aEntityID))
        {
            if (const auto& gameObject = Red::Cast<Red::GameObject>(entity))
            {
                gameObject->tags.Remove(aTag);
                Raw::TagSystem::UnassignTag(m_entityTagSystem, aEntityID, aTag);
            }
        }
    }

    return true;
}

bool App::DynamicEntitySystem::IsPopulated(Red::CName aTag)
{
    if (!m_ready)
        return false;

    std::shared_lock _(m_entityTagsLock);

    const auto taggedIt = m_entityIDsByTag.find(aTag);
    if (taggedIt == m_entityIDsByTag.end())
        return false;

    return !taggedIt.value().empty();
}

Red::EntityID App::DynamicEntitySystem::GetTaggedID(Red::CName aTag)
{
    if (!m_ready)
        return {};

    std::shared_lock _(m_entityTagsLock);

    const auto taggedIt = m_entityIDsByTag.find(aTag);
    if (taggedIt == m_entityIDsByTag.end())
        return {};

    if (taggedIt.value().empty())
        return {};

    return *taggedIt.value().begin();
}

Red::DynArray<Red::EntityID> App::DynamicEntitySystem::GetTaggedIDs(Red::CName aTag)
{
    if (!m_ready)
        return {};

    Red::DynArray<Red::EntityID> out;

    std::shared_lock _(m_entityTagsLock);

    const auto taggedIt = m_entityIDsByTag.find(aTag);
    if (taggedIt != m_entityIDsByTag.end())
    {
        for (const auto& entityID : taggedIt.value())
        {
            out.PushBack(entityID);
        }
    }

    return out;
}

Red::DynArray<Red::Handle<Red::Entity>> App::DynamicEntitySystem::GetTagged(Red::CName aTag)
{
    if (!m_ready)
        return {};

    Red::DynArray<Red::Handle<Red::Entity>> out;
    Red::Handle<Red::Entity> entity;

    std::shared_lock _(m_entityTagsLock);

    const auto taggedIt = m_entityIDsByTag.find(aTag);
    if (taggedIt != m_entityIDsByTag.end())
    {
        for (const auto& entityID : taggedIt.value())
        {
            entity = m_populationSystem->FindEntity(entityID);

            if (entity)
            {
                out.PushBack(entity);
            }
        }
    }

    return out;
}

void App::DynamicEntitySystem::DeleteTagged(Red::CName aTag)
{
    if (!m_ready)
        return;

    Core::Set<Red::EntityID> tagged;
    {
        std::unique_lock _(m_entityTagsLock);
        const auto taggedIt = m_entityIDsByTag.find(aTag);
        if (taggedIt != m_entityIDsByTag.end())
        {
            tagged = std::move(m_entityIDsByTag[aTag]);
        }
    }

    for (const auto& entityID : tagged)
    {
        DeleteEntity(entityID);
    }
}

void App::DynamicEntitySystem::EnableTagged(Red::CName aTag)
{
    if (!m_ready)
        return;

    Core::Set<Red::EntityID> tagged;
    {
        std::shared_lock _(m_entityTagsLock);
        const auto taggedIt = m_entityIDsByTag.find(aTag);
        if (taggedIt != m_entityIDsByTag.end())
        {
            tagged = m_entityIDsByTag[aTag];
        }
    }

    for (const auto& entityID : tagged)
    {
        EnableEntity(entityID);
    }
}

void App::DynamicEntitySystem::DisableTagged(Red::CName aTag)
{
    if (!m_ready)
        return;

    Core::Set<Red::EntityID> tagged;
    {
        std::shared_lock _(m_entityTagsLock);
        const auto taggedIt = m_entityIDsByTag.find(aTag);
        if (taggedIt != m_entityIDsByTag.end())
        {
            tagged = m_entityIDsByTag[aTag];
        }
    }

    for (const auto& entityID : tagged)
    {
        DisableEntity(entityID);
    }
}

void App::DynamicEntitySystem::RegisterListener(Red::CName aTag, const Red::Handle<Red::IScriptable>& aTarget,
                                                Red::CName aFunction)
{
    if (!m_ready)
        return;

    std::unique_lock _(m_listenersLock);

    m_listenersByTag[aTag].push_back({aTarget, aFunction});
}

void App::DynamicEntitySystem::UnregisterListener(Red::CName aTag, const Red::Handle<Red::IScriptable>& aTarget,
                                                  Red::CName aFunction)
{
    if (!m_ready)
        return;

    std::unique_lock _(m_listenersLock);

    auto listenersIt = m_listenersByTag.find(aTag);
    if (listenersIt != m_listenersByTag.end())
    {
        std::erase_if(listenersIt.value(), [&](EventListener& aListener) {
            return aListener.target.instance == aTarget.instance && aListener.function == aFunction;
        });
    }
}

void App::DynamicEntitySystem::UnregisterListeners(Red::CName aTag)
{
    if (!m_ready)
        return;

    std::unique_lock _(m_listenersLock);

    m_listenersByTag.erase(aTag);
}

void App::DynamicEntitySystem::ProcessListeners(Red::EntityID aEntityID, App::DynamicEntityEventType aType,
                                                const Red::DynArray<Red::CName>& aTags)
{
    for (const auto& tag : aTags)
    {
        Core::Vector<EventListener> listeners;
        {
            std::shared_lock _(m_listenersLock);
            const auto& listenersIt = m_listenersByTag.find(tag);

            if (listenersIt == m_listenersByTag.end())
                continue;

            listeners = listenersIt.value();
        }

        auto event = Red::MakeHandle<DynamicEntityEvent>(aType, aEntityID, tag);

        for (const auto& listener : listeners)
        {
            if (!listener.target.Expired())
            {
                Red::CallVirtual(listener.target.Lock(), listener.function, event);
            }
        }

        // TODO: Auto remove expired listeners
    }
}

void App::DynamicEntitySystem::ProcessListeners(Red::EntityID aEntityID, App::DynamicEntityEventType aType)
{
    ProcessListeners(aEntityID, aType, GetTags(aEntityID));
}

void App::DynamicEntitySystem::ProcessListeners(Red::EntityID aEntityID, Red::gameEntitySpawnerEventType aType)
{
    ProcessListeners(aEntityID, static_cast<DynamicEntityEventType>(static_cast<uint32_t>(aType)));
}

bool App::DynamicEntitySystem::ValidateEntitySpec(const App::DynamicEntitySpecPtr& aEntitySpec)
{
    if (aEntitySpec->IsRecord())
    {
        return Red::RecordExists(aEntitySpec->recordID, Red::GetClass<Red::gamedataSpawnableObject_Record>());
    }

    if (aEntitySpec->IsTemplate())
    {
        return Red::ResourceDepot::Get()->ResourceExists(aEntitySpec->templatePath.path);
    }

    return false;
}

Red::TweakDBID App::DynamicEntitySystem::ConvertTemplateToRecord(Red::RaRef<> aTemplate)
{
    const auto hash = Red::FNV1a32(reinterpret_cast<const uint8_t*>(&aTemplate.path), sizeof(Red::ResourcePath));
    const auto recordID = Red::TweakDBID(hash, 1);

    if (!Red::RecordExists(recordID))
    {
        Red::CreateFlat(recordID, ".entityTemplatePath", aTemplate);
        Red::CreateRecord(recordID, "SpawnableObject");
    }

    return recordID;
}
