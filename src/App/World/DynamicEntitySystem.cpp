#include "DynamicEntitySystem.hpp"
#include "Red/RuntimeScene.hpp"
#include "Red/TagSystem.hpp"
#include "Red/TweakDB.hpp"

namespace
{
constexpr auto SystemPersistentID = Red::PersistentID(Red::GetTypeName<App::DynamicEntitySystem>());
}

void App::DynamicEntitySystem::OnWorldAttached(Red::world::RuntimeScene*)
{
    m_persistencySystem = Red::GetGameSystem<Red::IPersistencySystem>();
    m_entityIDSystem = Red::GetGameSystem<Red::IDynamicEntityIDSystem>();
    m_entityStubSystem = Red::GetGameSystem<Red::IEntityStubSystem>();
    m_entityTagSystem = Raw::GameTagSystem::TagSystem::Ptr(Red::GetGameSystem<Red::GameTagSystem>());
    m_entityRegistry = Red::GetRuntimeSystem<Red::worldRuntimeEntityRegistry>();
    m_populationSystem = Red::GetGameSystem<Red::IPopulationSystem>();
    m_spawnEventBroadcaster = Red::GetGameSystem<Red::IEntitySpawnerEventsBroadcaster>();
    m_persistentStateType = Red::GetClass<DynamicEntitySystemPS>();
    m_ready = true;
}

void App::DynamicEntitySystem::OnStreamingWorldLoaded(Red::world::RuntimeScene*, uint64_t aRestored,
                                                      const Red::JobGroup&)
{
    m_restored = aRestored;

    m_spawnEventListenerID = m_spawnEventBroadcaster->RegisterListener(
        {this, &DynamicEntitySystem::OnEntitySpawnerEvent}, "");

    m_persistencySystem->GetPersistentState(m_persistentState, SystemPersistentID, m_persistentStateType, true);
    m_persistentState->RestoreAfterLoading();

    for (const auto& entityState : m_persistentState->GetEntityStates())
    {
        if (!entityState->entitySpec->persistState)
        {
            RemovePersistentState(entityState);
            UpdateTransientID(entityState);
        }

        RestoreEntityState(entityState);
    }

    m_persistentState->Clear();

    if (!m_entityStates.empty())
    {
        std::shared_lock _(m_entityStateLock);
        for (const auto& entityState : m_entityStates)
        {
            if (entityState->entitySpec->persistSpawn && entityState->entitySpec->active)
            {
                RespawnFromEntityState(entityState);
            }
        }
    }
}

uint32_t App::DynamicEntitySystem::OnBeforeGameSave(const Red::JobGroup& aJobGroup, void* a2)
{
    std::shared_lock _(m_entityStateLock);

    for (const auto& entityState : m_entityStates)
    {
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
    m_persistentState->Clear();
}

void App::DynamicEntitySystem::OnBeforeWorldDetach(Red::world::RuntimeScene* aScene)
{
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

    {
        std::unique_lock _(m_entityStateLock);
        m_entityStates.clear();
        m_entityStateByID.clear();
        m_entityStatesByTag.clear();
    }

    {
        std::unique_lock _(m_listenersLock);
        m_listenersByTag.clear();
    }
}

void App::DynamicEntitySystem::OnEntitySpawnerEvent(Red::game::EntitySpawnerEventType aType, Red::EntityID aEntityID,
                                                    Red::EntityID, Red::EntityStub* aStub)
{
    if (aType == Red::game::EntitySpawnerEventType::Spawn)
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

    Red::EntityID entityID{};

    if (aEntitySpec->persistState)
    {
        m_entityIDSystem->GetNextPersistableID(entityID);
    }
    else
    {
        m_entityIDSystem->GetNextTransientID(entityID);
    }

    if (!entityID.IsDefined())
        return {};

    auto entityState = CreateEntityState(entityID, aEntitySpec);

    if (aEntitySpec->active)
    {
        SpawnFromEntityState(entityState);
    }

    return entityID;
}

bool App::DynamicEntitySystem::DeleteEntity(Red::EntityID aEntityID)
{
    if (!m_ready)
        return false;

    auto entityState = RemoveEntityState(aEntityID);

    if (!entityState)
        return false;

    if (entityState->entitySpec->active && entityState->entityStub && IsSpawned(aEntityID))
    {
        ProcessListeners(aEntityID, DynamicEntityEventType::Despawned, entityState->entitySpec->tags);
    }

    DespawnFromEntityState(entityState);
    RemovePersistentState(entityState);

    return true;
}

bool App::DynamicEntitySystem::EnableEntity(Red::EntityID aEntityID)
{
    if (!m_ready)
        return false;

    std::unique_lock _(m_entityStateLock);
    auto entityStateIt = m_entityStateByID.find(aEntityID);

    if (entityStateIt == m_entityStateByID.end())
        return false;

    auto& entityState = entityStateIt.value();

    if (entityState->entitySpec->active)
        return true;

    entityState->entitySpec->active = true;

    return RespawnFromEntityState(entityState);
}

bool App::DynamicEntitySystem::DisableEntity(Red::EntityID aEntityID)
{
    if (!m_ready)
        return false;

    std::unique_lock _(m_entityStateLock);
    auto entityStateIt = m_entityStateByID.find(aEntityID);

    if (entityStateIt == m_entityStateByID.end())
        return false;

    auto& entityState = entityStateIt.value();

    if (!entityState->entitySpec->active)
        return true;

    entityState->entitySpec->active = false;

    return DespawnFromEntityState(entityState);
}

bool App::DynamicEntitySystem::SpawnFromEntityState(const App::DynamicEntityStatePtr& aEntityState)
{
    Red::EntityStubTokenPtr token{};
    Red::EntityStubCreateRequest request{aEntityState->entityID,
                                         aEntityState->entitySpec->position,
                                         aEntityState->entitySpec->orientation,
                                         aEntityState->entitySpec->recordID};

    m_entityStubSystem->CreateStub(token, request, [this, aEntityState](Red::EntityStubTokenPtr& aToken) {
        if (aToken->status != Red::EntityStubStatus::Created)
        {
            DeleteEntity(aEntityState->entityID);
            return;
        }

        RegisterPopulation(aEntityState, false);
        AcquireEntityStub(aEntityState, aToken);
    });

    return true;
}

bool App::DynamicEntitySystem::RespawnFromEntityState(const App::DynamicEntityStatePtr& aEntityState)
{
    if (aEntityState->entityStub)
    {
        RegisterPopulation(aEntityState, true);
        return true;
    }

    if (!aEntityState->entitySpec->persistState)
    {
        return SpawnFromEntityState(aEntityState);
    }

    const auto persistenceStatus = m_persistencySystem->GetEntityStatus(aEntityState->entityID);

    if (persistenceStatus != Red::EntityPersistenceStatus::Persisted)
        return false;

    Red::EntityStubTokenPtr token{};
    Red::EntityStubRestoreRequest request{aEntityState->entityID, aEntityState->entitySpec->recordID};

    m_entityStubSystem->RestoreStub(token, request, [this, aEntityState](Red::EntityStubTokenPtr& aToken) {
        if (aToken->status != Red::EntityStubStatus::Created)
        {
            DeleteEntity(aEntityState->entityID);
            return;
        }

        RegisterPopulation(aEntityState, true);
        AcquireEntityStub(aEntityState, aToken);
    });

    return true;
}

bool App::DynamicEntitySystem::DespawnFromEntityState(const App::DynamicEntityStatePtr& aEntityState)
{
    if (aEntityState->entityStub)
    {
        RemovePopulation(aEntityState);

        if (aEntityState->entitySpec->persistState)
        {
            ResetEntityStub(aEntityState);
        }
        else
        {
            RemoveEntityStub(aEntityState);
        }
    }

    return true;
}

void App::DynamicEntitySystem::RegisterPopulation(const App::DynamicEntityStatePtr& aEntityState, bool aRespawn)
{
    Red::PopulationEntityRegisterRequest request{};
    request.entityID = aEntityState->entityID;
    request.spawnInView = aEntityState->entitySpec->spawnInView;
    request.alwaysSpawned = aEntityState->entitySpec->alwaysSpawned;

    if (!aRespawn)
    {
        if (aEntityState->entitySpec->appearanceName)
        {
            request.appearanceName = aEntityState->entitySpec->appearanceName;
            request.prefetchAppearance = true;
        }
    }

    m_populationSystem->RegisterEntity(request);
}

void App::DynamicEntitySystem::RemovePopulation(const App::DynamicEntityStatePtr& aEntityState)
{
    m_populationSystem->RemoveEntity(aEntityState->entityID, 0);
}

void App::DynamicEntitySystem::RemovePersistentState(const App::DynamicEntityStatePtr& aEntityState)
{
    m_persistencySystem->RemoveDynamicEntityState(aEntityState->entityID);
}

void App::DynamicEntitySystem::AcquireEntityStub(const App::DynamicEntityStatePtr& aEntityState,
                                                 Red::EntityStubTokenPtr& aToken)
{
    std::unique_lock _(m_entityStateLock);
    aEntityState->AcquireStub(*aToken);
}

void App::DynamicEntitySystem::ResetEntityStub(const App::DynamicEntityStatePtr& aEntityState)
{
    std::unique_lock _(m_entityStateLock);
    aEntityState->ResetStub();
}

void App::DynamicEntitySystem::RemoveEntityStub(const App::DynamicEntityStatePtr& aEntityState)
{
    std::unique_lock _(m_entityStateLock);
    m_entityStubSystem->DeleteStub(aEntityState->entityStub);
}

App::DynamicEntityStatePtr App::DynamicEntitySystem::CreateEntityState(Red::EntityID aEntityID,
                                                                       const App::DynamicEntitySpecPtr& aEntitySpec)
{
    auto entityState = Red::MakeHandle<DynamicEntityState>(aEntityID, *aEntitySpec);
    auto& entitySpec = entityState->entitySpec;

    if (entitySpec->IsTemplate())
    {
        entitySpec->recordID = ConvertTemplateToRecord(entitySpec->templatePath);
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

    AddEntityState(aEntityState);
}

void App::DynamicEntitySystem::AddEntityState(const App::DynamicEntityStatePtr& aEntityState)
{
    std::unique_lock _(m_entityStateLock);

    m_entityStates.emplace_back(aEntityState);
    m_entityStateByID.insert({aEntityState->entityID, aEntityState});

    for (const auto& tag : aEntityState->entitySpec->tags)
    {
        m_entityStatesByTag[tag].insert(aEntityState->entityID);
    }
}

void App::DynamicEntitySystem::UpdateTransientID(const App::DynamicEntityStatePtr& aEntityState)
{
    m_entityIDSystem->GetNextTransientID(aEntityState->entityID);
}

App::DynamicEntityStatePtr App::DynamicEntitySystem::RemoveEntityState(Red::EntityID aEntityID)
{
    std::unique_lock _(m_entityStateLock);
    auto entityStateIt = m_entityStateByID.find(aEntityID);

    if (entityStateIt == m_entityStateByID.end())
        return {};

    auto entityState = entityStateIt.value();

    for (const auto& tag : entityState->entitySpec->tags)
    {
        m_entityStatesByTag[tag].erase(entityState->entityID);
    }

    m_entityStateByID.erase(entityState->entityID);
    std::erase(m_entityStates, entityState);

    return entityState;
}

bool App::DynamicEntitySystem::IsManaged(Red::EntityID aEntityID)
{
    if (!m_ready)
        return false;

    std::shared_lock _(m_entityStateLock);

    return m_entityStateByID.contains(aEntityID);
}

bool App::DynamicEntitySystem::IsTagged(Red::EntityID aEntityID, Red::CName aTag)
{
    if (!m_ready)
        return false;

    std::shared_lock _(m_entityStateLock);
    auto entityStateIt = m_entityStateByID.find(aEntityID);

    if (entityStateIt == m_entityStateByID.end())
        return false;

    auto& entityState = entityStateIt.value();

    for (const auto& tag : entityState->entitySpec->tags)
    {
        if (tag == aTag)
            return true;
    }

    return false;
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

    Red::Handle<Red::Entity> entity;
    m_populationSystem->FindEntity(entity, aEntityID);

    return entity;
}

Red::DynArray<Red::CName> App::DynamicEntitySystem::GetTags(Red::EntityID aEntityID)
{
    if (!m_ready)
        return {};

    std::shared_lock _(m_entityStateLock);
    auto entityStateIt = m_entityStateByID.find(aEntityID);

    if (entityStateIt == m_entityStateByID.end())
        return {};

    auto& entityState = entityStateIt.value();
    return entityState->entitySpec->tags;
}

bool App::DynamicEntitySystem::AssignTag(Red::EntityID aEntityID, Red::CName aTag)
{
    if (!m_ready)
        return false;

    std::unique_lock _(m_entityStateLock);
    auto entityStateIt = m_entityStateByID.find(aEntityID);

    if (entityStateIt == m_entityStateByID.end())
        return false;

    auto& entityState = entityStateIt.value();

    if (!m_entityStatesByTag[aTag].contains(aEntityID))
    {
        m_entityStatesByTag[aTag].insert(aEntityID);
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

    std::unique_lock _(m_entityStateLock);
    auto entityStateIt = m_entityStateByID.find(aEntityID);

    if (entityStateIt == m_entityStateByID.end())
        return false;

    auto& entityState = entityStateIt.value();

    if (m_entityStatesByTag[aTag].contains(aEntityID))
    {
        m_entityStatesByTag[aTag].erase(aEntityID);
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

    std::shared_lock _(m_entityStateLock);

    return !m_entityStatesByTag[aTag].empty();
}

Red::EntityID App::DynamicEntitySystem::GetTaggedID(Red::CName aTag)
{
    if (!m_ready)
        return {};

    std::shared_lock _(m_entityStateLock);
    auto& tagged = m_entityStatesByTag[aTag];

    if (tagged.empty())
        return {};

    return *tagged.begin();
}

Red::DynArray<Red::EntityID> App::DynamicEntitySystem::GetTaggedIDs(Red::CName aTag)
{
    if (!m_ready)
        return {};

    std::shared_lock _(m_entityStateLock);
    Red::DynArray<Red::EntityID> out;

    for (const auto& entityID : m_entityStatesByTag[aTag])
    {
        out.PushBack(entityID);
    }

    return out;
}

Red::DynArray<Red::Handle<Red::Entity>> App::DynamicEntitySystem::GetTagged(Red::CName aTag)
{
    if (!m_ready)
        return {};

    std::shared_lock _(m_entityStateLock);
    Red::DynArray<Red::Handle<Red::Entity>> out;
    Red::Handle<Red::Entity> entity;

    for (const auto& entityID : m_entityStatesByTag[aTag])
    {
        m_populationSystem->FindEntity(entity, entityID);

        if (entity)
        {
            out.PushBack(entity);
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
        std::unique_lock _(m_entityStateLock);
        tagged = std::move(m_entityStatesByTag[aTag]);
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
        std::shared_lock _(m_entityStateLock);
        tagged = m_entityStatesByTag[aTag];
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
        std::shared_lock _(m_entityStateLock);
        tagged = m_entityStatesByTag[aTag];
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
                                                Red::DynArray<Red::CName>& aTags)
{
    for (auto& tag : aTags)
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
    auto tags = GetTags(aEntityID);

    if (tags.size)
    {
        ProcessListeners(aEntityID, aType, tags);
    }
}

void App::DynamicEntitySystem::ProcessListeners(Red::EntityID aEntityID, Red::game::EntitySpawnerEventType aType)
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
