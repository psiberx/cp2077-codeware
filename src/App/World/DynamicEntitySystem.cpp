#include "DynamicEntitySystem.hpp"
#include "Red/RuntimeScene.hpp"
#include "Red/TagSystem.hpp"
#include "Red/TweakDB.hpp"

namespace
{
constexpr auto SystemPersistentID = Red::PersistentID(Red::GetTypeName<App::DynamicEntitySystem>());
}

void App::DynamicEntitySystem::OnWorldAttached(Red::worldRuntimeScene*)
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

void App::DynamicEntitySystem::OnStreamingWorldLoaded(Red::worldRuntimeScene*, uint64_t aRestored,
                                                      const Red::JobGroup&)
{
    m_restored = aRestored;

    m_spawnEventListenerID = m_spawnEventBroadcaster->RegisterListener(
        {this, &DynamicEntitySystem::OnEntitySpawnerEvent}, "");

    m_persistencySystem->GetPersistentState(m_persistentState, SystemPersistentID, m_persistentStateType, true);
    m_persistentState->RestoreAfterLoading();

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
    m_persistentState->Clear();
}

void App::DynamicEntitySystem::OnBeforeWorldDetach(Red::worldRuntimeScene* aScene)
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
    Red::EntityStubTokenPtr token{};
    Red::EntityStubCreateRequest request{aEntityState->entityID,
                                         aEntityState->entitySpec->position,
                                         aEntityState->entitySpec->orientation,
                                         aEntityState->entitySpec->recordID};

    m_entityStubSystem->CreateStub(token, request, [this, aEntityState](Red::EntityStubTokenPtr& aToken) {
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
    });

    return true;
}

bool App::DynamicEntitySystem::DespawnFromEntityState(const App::DynamicEntityStatePtr& aEntityState)
{
    if (auto entityStub = aEntityState->ExtractStub())
    {
        m_populationSystem->RemoveEntity(aEntityState->entityID, 0);
        m_entityStubSystem->DeleteStub(std::move(entityStub));

        return true;
    }

    return false;
}

App::DynamicEntityStatePtr App::DynamicEntitySystem::CreateEntityState(const App::DynamicEntitySpecPtr& aEntitySpec)
{
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
        m_entityIDSystem->GetNextTransientID(aEntityState->entityID);
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

    return m_entityIDsByTag[aTag].contains(aEntityID);
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

    if (!m_entityIDsByTag[aTag].contains(aEntityID))
    {
        m_entityIDsByTag[aTag].insert(aEntityID);

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

    if (m_entityIDsByTag[aTag].contains(aEntityID))
    {
        m_entityIDsByTag[aTag].erase(aEntityID);

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

    return !m_entityIDsByTag[aTag].empty();
}

Red::EntityID App::DynamicEntitySystem::GetTaggedID(Red::CName aTag)
{
    if (!m_ready)
        return {};

    std::shared_lock _(m_entityTagsLock);

    auto& tagged = m_entityIDsByTag[aTag];
    if (tagged.empty())
        return {};

    return *tagged.begin();
}

Red::DynArray<Red::EntityID> App::DynamicEntitySystem::GetTaggedIDs(Red::CName aTag)
{
    if (!m_ready)
        return {};

    std::shared_lock _(m_entityTagsLock);

    Red::DynArray<Red::EntityID> out;

    for (const auto& entityID : m_entityIDsByTag[aTag])
    {
        out.PushBack(entityID);
    }

    return out;
}

Red::DynArray<Red::Handle<Red::Entity>> App::DynamicEntitySystem::GetTagged(Red::CName aTag)
{
    if (!m_ready)
        return {};

    std::shared_lock _(m_entityTagsLock);

    Red::DynArray<Red::Handle<Red::Entity>> out;
    Red::Handle<Red::Entity> entity;

    for (const auto& entityID : m_entityIDsByTag[aTag])
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
        std::unique_lock _(m_entityTagsLock);
        tagged = std::move(m_entityIDsByTag[aTag]);
        // m_entityIDsByTag[aTag].clear();
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
        tagged = m_entityIDsByTag[aTag];
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
        tagged = m_entityIDsByTag[aTag];
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
