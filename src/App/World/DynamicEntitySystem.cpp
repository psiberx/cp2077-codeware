#include "DynamicEntitySystem.hpp"

namespace
{
constexpr auto SystemPersistentID = Red::PersistentID(Red::GetTypeName<App::DynamicEntitySystem>());
}

void App::DynamicEntitySystem::OnWorldAttached(Red::world::RuntimeScene* aScene)
{
    m_entityStates.clear();
    m_entityStateByID.clear();
    m_entityStatesByTag.clear();

    m_persistentStateType = Red::GetClass<DynamicEntitySystemPS>();
    m_persistentState.Reset();

    m_tweakDB = Red::TweakDB::Get();;
    m_persistencySystem = Red::GetGameSystem<Red::IPersistencySystem>();
    m_entityIDSystem = Red::GetGameSystem<Red::IDynamicEntityIDSystem>();
    m_entityStubSystem = Red::GetGameSystem<Red::IEntityStubSystem>();
    m_populationSystem = Red::GetGameSystem<Red::IPopulationSystem>();
}

bool App::DynamicEntitySystem::OnGameRestored()
{
    m_persistencySystem->GetPersistentState(m_persistentState, SystemPersistentID, m_persistentStateType, true);

    for (const auto& entityState : m_persistentState->m_entityStates)
    {
        entityState->entitySpec->PrepareForRestoring();
        RestoreEntityState(entityState);

        if (!entityState->entitySpec->persistState)
        {
            RemovePersistentState(entityState);
        }

        if (entityState->entitySpec->persistSpawn && entityState->entitySpec->active)
        {
            RespawnFromEntityState(entityState);
        }
    }

    m_persistentState->m_entityStates.Clear();

    return true;
}

uint32_t App::DynamicEntitySystem::OnBeforeGameSave(const Red::JobGroup& aJobGroup, void* a2)
{
    for (const auto& entityState : m_entityStates)
    {
        if (entityState->entitySpec->persistState || entityState->entitySpec->persistSpawn)
        {
            entityState->entitySpec->PrepareForSaving();
            m_persistentState->m_entityStates.PushBack(entityState);
        }
    }

    return 0;
}

void App::DynamicEntitySystem::OnAfterGameSave()
{
    m_persistentState->m_entityStates.Clear();
}

void App::DynamicEntitySystem::OnBeforeWorldDetach(Red::world::RuntimeScene* aScene)
{
}

void App::DynamicEntitySystem::OnRegisterUpdates(Red::UpdateRegistrar* aRegistrar)
{
    // aRegistrar->RegisterUpdate(Red::UpdateTickGroup::FrameBegin, this, "DynamicEntitySystem/Tick",
    //                            {this, &DynamicEntitySystem::OnUpdateTick});
}

void App::DynamicEntitySystem::OnUpdateTick(Red::FrameInfo& aFrame, Red::JobQueue& aJobQueue)
{
}

Red::EntityID App::DynamicEntitySystem::CreateEntity(const DynamicEntitySpecPtr& aEntitySpec)
{
    if (!aEntitySpec->IsValid())
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
    auto entityStateIt = m_entityStateByID.find(aEntityID);

    if (entityStateIt == m_entityStateByID.end())
        return false;

    auto& entityState = entityStateIt.value();

    DespawnFromEntityState(entityState);
    RemovePersistentState(entityState);
    RemoveEntityStub(entityState);
    RemoveEntityState(entityState);

    return true;
}

bool App::DynamicEntitySystem::EnableEntity(Red::EntityID aEntityID)
{
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
            RemoveEntityState(aEntityState);
            return;
        }

        RegisterPopulation(aEntityState, false);
        aEntityState->TakeoveStub(*aToken);
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
        m_entityIDSystem->GetNextTransientID(aEntityState->entityID);

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
            RemoveEntityState(aEntityState);
            return;
        }

        RegisterPopulation(aEntityState, true);
        aEntityState->TakeoveStub(*aToken);
    });

    return true;
}

bool App::DynamicEntitySystem::DespawnFromEntityState(const App::DynamicEntityStatePtr& aEntityState)
{
    RemovePopulation(aEntityState);

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
    m_populationSystem->RemoveEntity(aEntityState->entityID, "");
}

void App::DynamicEntitySystem::RemovePersistentState(const App::DynamicEntityStatePtr& aEntityState)
{
    m_persistencySystem->RemoveDynamicEntityState(aEntityState->entityID);
}

void App::DynamicEntitySystem::RemoveEntityStub(const App::DynamicEntityStatePtr& aEntityState)
{
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
    m_entityStates.emplace_back(aEntityState);
    m_entityStateByID.insert({aEntityState->entityID, aEntityState});

    for (const auto& tag : aEntityState->entitySpec->tags)
    {
        m_entityStatesByTag[tag].insert(aEntityState->entityID);
    }
}

void App::DynamicEntitySystem::RemoveEntityState(const App::DynamicEntityStatePtr& aEntityState)
{
    for (const auto& tag : aEntityState->entitySpec->tags)
    {
        m_entityStatesByTag[tag].erase(aEntityState->entityID);
    }

    m_entityStateByID.erase(aEntityState->entityID);
    std::erase(m_entityStates, aEntityState);
}

Red::DynArray<Red::CName> App::DynamicEntitySystem::GetTags(Red::EntityID aEntityID)
{
    auto entityStateIt = m_entityStateByID.find(aEntityID);

    if (entityStateIt == m_entityStateByID.end())
        return {};

    auto& entityState = entityStateIt.value();
    return entityState->entitySpec->tags;
}

void App::DynamicEntitySystem::AssignTag(Red::EntityID aEntityID, Red::CName aTag)
{
    m_entityStatesByTag[aTag].insert(aEntityID);
}

void App::DynamicEntitySystem::UnassignTag(Red::EntityID aEntityID, Red::CName aTag)
{
    m_entityStatesByTag[aTag].erase(aEntityID);
}

bool App::DynamicEntitySystem::IsPopulated(Red::CName aTag)
{
    return !m_entityStatesByTag[aTag].empty();
}

Red::EntityID App::DynamicEntitySystem::GetEntityID(Red::CName aTag)
{
    auto& tagged = m_entityStatesByTag[aTag];

    if (tagged.empty())
        return {};

    return *tagged.begin();
}

Red::DynArray<Red::EntityID> App::DynamicEntitySystem::GetEntityIDs(Red::CName aTag)
{
    Red::DynArray<Red::EntityID> out;

    for (const auto& entityID : m_entityStatesByTag[aTag])
    {
        out.PushBack(entityID);
    }

    return out;
}

void App::DynamicEntitySystem::DeleteTagged(Red::CName aTag)
{
    auto tagged = std::move(m_entityStatesByTag[aTag]);

    for (const auto& entityID : tagged)
    {
        DeleteEntity(entityID);
    }
}

void App::DynamicEntitySystem::EnableTagged(Red::CName aTag)
{
    auto& tagged = m_entityStatesByTag[aTag];

    for (const auto& entityID : tagged)
    {
        EnableEntity(entityID);
    }
}

void App::DynamicEntitySystem::DisableTagged(Red::CName aTag)
{
    auto& tagged = m_entityStatesByTag[aTag];

    for (const auto& entityID : tagged)
    {
        DisableEntity(entityID);
    }
}

Red::TweakDBID App::DynamicEntitySystem::ConvertTemplateToRecord(Red::RaRef<> aTemplate)
{
    const auto hash = Red::FNV1a32(reinterpret_cast<const uint8_t*>(&aTemplate.path), sizeof(Red::ResourcePath));
    const auto recordID = Red::TweakDBID(hash, 1);
    Red::Handle<Red::IScriptable>* record;

    {
        std::shared_lock _(m_tweakDB->mutex01);
        record = m_tweakDB->recordsByID.Get(recordID);
    }

    if (!record)
    {
        {
            static const auto type = Red::GetType<Red::RaRef<>>();
            const auto offset = m_tweakDB->CreateFlatValue({type, &aTemplate});
            auto flatID = Red::TweakDBID(recordID, ".entityTemplatePath");
            flatID.SetTDBOffset(offset);
            m_tweakDB->AddFlat(flatID);
        }
        {
            static const auto recordHash = Red::Murmur3_32(reinterpret_cast<const uint8_t*>("SpawnableObject"), 15);
            using CreateTDBRecord_t = void (*)(Red::TweakDB*, uint32_t, Red::TweakDBID);
            Red::RelocFunc<CreateTDBRecord_t> CreateTDBRecord(Red::Addresses::TweakDB_CreateRecord);
            CreateTDBRecord(m_tweakDB, recordHash, recordID);
        }
    }

    return recordID;
}
