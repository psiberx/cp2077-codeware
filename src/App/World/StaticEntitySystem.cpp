#include "StaticEntitySystem.hpp"
#include "Red/Entity.hpp"
#include "Red/RuntimeScene.hpp"
#if defined(__APPLE__)
#include "MacEngine.hpp"
#include "MacR21.hpp"
#include "MacDiag.hpp"
#endif

void App::StaticEntitySystem::OnWorldAttached(Red::world::RuntimeScene*)
{
#if defined(__APPLE__)
    if (!Red::MacSystemEnabled("StaticEntitySystem"))
    {
        Red::MacSystemOff("StaticEntitySystem", "switched off with CODEWARE_MAC_SYSTEMS_OFF");
        return;
    }
#endif
    m_entityIDSystem = Red::GetGameSystem<Red::IDynamicEntityIDSystem>();
    m_entityRuntimeSystem = Red::GetRuntimeSystem<Red::worldRuntimeSystemEntity>();
#if defined(__APPLE__)
    if (!m_entityRuntimeSystem)
    {
        Red::MacSystemOff("StaticEntitySystem", "the runtime entity system is not reachable");
        return;
    }
#endif
    m_entitySpawner = Raw::RuntimeSystemEntity::Spawner::Ref(m_entityRuntimeSystem);
    m_entityRegistry = Red::GetRuntimeSystem<Red::worldRuntimeEntityRegistry>();
    m_ready = true;
#if defined(__APPLE__)
    // SELFTEST R18. The systems it needs are all reachable at the world attach.
    MAC_DIAG( "[cw] R18 StaticEntitySystem ready idSystem=%p runtimeEntity=%p spawner=%p registry=%p\n",
                 static_cast<void*>(m_entityIDSystem), static_cast<void*>(m_entityRuntimeSystem),
                 static_cast<void*>(m_entitySpawner), static_cast<void*>(m_entityRegistry));
    Mac::R18Check(m_entityIDSystem && m_entityRuntimeSystem && m_entityRegistry,
                  "StaticEntitySystem finds the entity ID system and the runtime entity system and registry");
#endif
}

void App::StaticEntitySystem::OnBeforeWorldDetach(Red::world::RuntimeScene*)
{
    {
        std::scoped_lock tokensLockR(m_tokensLock);
        m_tokens.clear();
    }

    {
        std::scoped_lock entitiesLockR(m_entitiesLock);
        for (auto& [entityID, entity] : m_entities)
        {
            (~Raw::Entity::Dispose)(entity);
        }
    }
}

void App::StaticEntitySystem::OnAfterWorldDetach()
{
    m_ready = false;

    std::scoped_lock _(m_entitiesLock, m_tagsLock, m_disposedLock);

    for (auto& [entityID, entity] : m_entities)
    {
        if (!Red::IsInstanceOf<Red::GameObject>(entity))
        {
            Raw::RuntimeEntityRegistry::UnregisterEntity(m_entityRegistry, entity);
        }
    }

    m_entities.clear();
    m_entityIDsByTag.clear();
    m_tagsByEntityID.clear();
    m_disposed.clear();
}

void App::StaticEntitySystem::OnRegisterUpdates(Red::UpdateRegistrar* aRegistrar)
{
#if defined(__APPLE__)
    {
        static auto& counter = Mac::HookCount("StaticEntitySystem_RegisterUpdates");
        Mac::Hit(counter);
        MAC_DIAG( "[cw] R21 StaticEntitySystem::OnRegisterUpdates registrar=%p\n", static_cast<void*>(aRegistrar));
        Mac::R21DumpRegistrar(aRegistrar, "before");
    }
    const uint32_t countBefore = Mac::R21RegistrarGroup0Count(aRegistrar);
#endif
    aRegistrar->RegisterUpdate(Red::UpdateTickGroup::FrameBegin, this, "StaticEntitySystem/Tick",
                               {this, &StaticEntitySystem::OnUpdateTick});
#if defined(__APPLE__)
    Mac::R21DumpRegistrar(aRegistrar, "after");
    Mac::R21CheckRegistration(aRegistrar, countBefore, "StaticEntitySystem/Tick", this);
#endif
}

void App::StaticEntitySystem::OnUpdateTick(Red::FrameInfo& aFrame, Red::JobQueue& aJobQueue)
{
#if defined(__APPLE__)
    {
        static auto& counter = Mac::HookCount("StaticEntitySystem_Tick");
        Mac::Hit(counter);
    }
#endif
    std::scoped_lock _(m_disposedLock);

    if (m_disposed.empty())
        return;

    for (auto it = m_disposed.begin(); it != m_disposed.end(); )
    {
        auto& entityID = it->first;
        auto& entity = it->second;

        auto& status = Raw::Entity::Status::Ref(entity);
        if (status != Red::EntityStatus::Uninitialized)
        {
            ++it;
            continue;
        }

        {
            std::scoped_lock entitiesLockRW(m_entitiesLock);
            m_entities.erase(entityID);
        }

        {
            std::scoped_lock tagsLockRW(m_tagsLock);
            auto tagsEntry = m_tagsByEntityID.find(entityID);
            if (tagsEntry != m_tagsByEntityID.end())
            {
                for (const auto& tag : tagsEntry.value())
                {
                    m_entityIDsByTag[tag].erase(entityID);
                }
                m_tagsByEntityID.erase(tagsEntry);
            }
        }

        it = m_disposed.erase(it);
    }
}

bool App::StaticEntitySystem::IsReady() const
{
    return m_ready;
}

Red::EntityID App::StaticEntitySystem::SpawnEntity(const StaticEntitySpecPtr& aEntitySpec)
{
    if (!m_ready)
        return {};

    if (!ValidateEntitySpec(aEntitySpec))
        return {};

    auto entityID = m_entityIDSystem->GetNextTransientID();

    if (!entityID.IsDefined())
        return {};

    Red::EntitySpawnerRequest request{};
    request.entityID = entityID;
    request.templatePath = aEntitySpec->templatePath.path;
    request.appearanceName = aEntitySpec->appearanceName;
    request.transform.Position = aEntitySpec->position;
    request.transform.Orientation = aEntitySpec->orientation;
    request.detached = !aEntitySpec->attached;

    request.callback = [this, entityID](const Red::SharedPtr<Red::EntitySpawnerToken>& aToken)
    {
        if (aToken->entity && !aToken->failed && !aToken->aborted)
        {
            std::scoped_lock _(m_tokensLock, m_entitiesLock);

            if (!Red::IsInstanceOf<Red::GameObject>(aToken->entity))
            {
                Raw::RuntimeEntityRegistry::RegisterEntity(m_entityRegistry, aToken->entity);
            }

            m_entities.insert_or_assign(entityID, std::move(aToken->entity));
            m_tokens.erase(entityID);
        }
        else
        {
            DespawnEntity(entityID);
        }
    };

    auto token = m_entitySpawner->SpawnEntity(request);

    if (!token)
        return {};

    {
        std::scoped_lock _(m_tokensLock);
        m_tokens.insert_or_assign(entityID, std::move(token));
    }

    {
        std::scoped_lock _(m_tagsLock);
        for (const auto& tag : aEntitySpec->tags)
        {
            m_entityIDsByTag[tag].insert(entityID);
            m_tagsByEntityID[entityID].insert(tag);
        }
    }

    return entityID;
}

bool App::StaticEntitySystem::DespawnEntity(Red::EntityID aEntityID)
{
    if (!m_ready)
        return false;

    {
        std::shared_lock disposedLockR(m_disposedLock);
        if (m_disposed.contains(aEntityID))
            return false;
    }

    auto tokenRemoved = false;
    auto entityRemoved = false;

    {
        std::scoped_lock _(m_tokensLock);
        tokenRemoved = m_tokens.erase(aEntityID);
    }

    {
        std::shared_lock entitiesLockR(m_entitiesLock);
        auto entityEntry = m_entities.find(aEntityID);
        if (entityEntry != m_entities.end())
        {
            auto& entity = entityEntry.value();

            (~Raw::Entity::Dispose)(entity);

            {
                std::scoped_lock disposedLockRW(m_disposedLock);
                m_disposed.insert_or_assign(aEntityID, entity);
            }

            // m_entities.erase(entityEntry);

            entityRemoved = true;
        }
    }

    return tokenRemoved || entityRemoved;
}

bool App::StaticEntitySystem::AttachEntity(Red::EntityID aEntityID)
{
    if (!m_ready)
        return false;

    auto entity = GetEntity(aEntityID);
    if (!entity)
        return false;

    auto& status = Raw::Entity::Status::Ref(entity);
    if (status == Red::EntityStatus::Attached || status == Red::EntityStatus::Attaching)
        return false;

    Raw::RuntimeSystemEntity::AttachEntity(m_entityRuntimeSystem, entity);

    return true;
}

bool App::StaticEntitySystem::DetachEntity(Red::EntityID aEntityID)
{
    if (!m_ready)
        return false;

    auto entity = GetEntity(aEntityID);
    if (!entity)
        return false;

    auto& status = Raw::Entity::Status::Ref(entity);
    if (status == Red::EntityStatus::Detached || status == Red::EntityStatus::Detaching)
        return false;

    Raw::RuntimeSystemEntity::DetachEntity(m_entityRuntimeSystem, entity, 0);

    return true;
}

bool App::StaticEntitySystem::IsManaged(Red::EntityID aEntityID)
{
    if (!m_ready)
        return false;

    {
        std::shared_lock _(m_entitiesLock);
        if (m_entities.contains(aEntityID))
            return true;
    }

    {
        std::shared_lock _(m_tokensLock);
        if (m_tokens.contains(aEntityID))
            return true;
    }

    return false;
}

bool App::StaticEntitySystem::IsTagged(Red::EntityID aEntityID, Red::CName aTag)
{
    if (!m_ready)
        return false;

    std::shared_lock _(m_tagsLock);

    const auto entityIDsEntry = m_entityIDsByTag.find(aTag);
    if (entityIDsEntry == m_entityIDsByTag.end())
        return false;

    return entityIDsEntry.value().contains(aEntityID);
}

bool App::StaticEntitySystem::IsSpawned(Red::EntityID aEntityID)
{
    if (!m_ready)
        return false;

    std::shared_lock _(m_entitiesLock);

    return m_entities.contains(aEntityID);
}

bool App::StaticEntitySystem::IsSpawning(Red::EntityID aEntityID)
{
    if (!m_ready)
        return false;

    std::shared_lock _(m_tokensLock);

    auto tokenEntry = m_tokens.find(aEntityID);
    if (tokenEntry == m_tokens.end())
        return false;

    auto& token = tokenEntry.value();

    return !token->entity && !token->failed && !token->aborted;
}

Red::Handle<Red::Entity> App::StaticEntitySystem::GetEntity(Red::EntityID aEntityID)
{
    if (!m_ready)
        return {};

    Red::Handle<Red::Entity> entity;

    {
        std::shared_lock _(m_entitiesLock);

        auto entityEntry = m_entities.find(aEntityID);
        if (entityEntry != m_entities.end())
        {
            entity = entityEntry.value();
        }
    }

    return entity;
}

Red::DynArray<Red::CName> App::StaticEntitySystem::GetTags(Red::EntityID aEntityID)
{
    if (!m_ready)
        return {};

    std::shared_lock _(m_tagsLock);

    auto tagsEntry = m_tagsByEntityID.find(aEntityID);
    if (tagsEntry == m_tagsByEntityID.end())
        return {};

    Red::DynArray<Red::CName> out;
    for (const auto& tag : tagsEntry.value())
    {
        out.PushBack(tag);
    }

    return out;
}

bool App::StaticEntitySystem::AssignTag(Red::EntityID aEntityID, Red::CName aTag)
{
    if (!m_ready)
        return false;

    {
        std::scoped_lock _(m_tagsLock);

        m_entityIDsByTag[aTag].insert(aEntityID);
        m_tagsByEntityID[aEntityID].insert(aTag);
    }

    return true;
}

bool App::StaticEntitySystem::UnassignTag(Red::EntityID aEntityID, Red::CName aTag)
{
    if (!m_ready)
        return false;

   {
        std::scoped_lock _(m_tagsLock);

        m_entityIDsByTag[aTag].erase(aEntityID);
        m_tagsByEntityID[aEntityID].erase(aTag);
    }

    return true;
}

bool App::StaticEntitySystem::IsPopulated(Red::CName aTag)
{
    if (!m_ready)
        return false;

    std::shared_lock _(m_tagsLock);

    const auto entityIDsEntry = m_entityIDsByTag.find(aTag);
    if (entityIDsEntry == m_entityIDsByTag.end())
        return false;

    return !entityIDsEntry.value().empty();
}

Red::EntityID App::StaticEntitySystem::GetTaggedID(Red::CName aTag)
{
    if (!m_ready)
        return {};

    std::shared_lock _(m_tagsLock);

    auto entityIDsEntry = m_entityIDsByTag.find(aTag);
    if (entityIDsEntry == m_entityIDsByTag.end())
        return {};

    auto entityIDs = entityIDsEntry.value();

    if (entityIDs.empty())
        return {};

    return *entityIDs.begin();
}

Red::DynArray<Red::EntityID> App::StaticEntitySystem::GetTaggedIDs(Red::CName aTag)
{
    if (!m_ready)
        return {};

    std::shared_lock _(m_tagsLock);

    auto entityIDsEntry = m_entityIDsByTag.find(aTag);
    if (entityIDsEntry == m_entityIDsByTag.end())
        return {};

    Red::DynArray<Red::EntityID> out;
    for (const auto& entityID : entityIDsEntry.value())
    {
        out.PushBack(entityID);
    }

    return out;
}

Red::DynArray<Red::Handle<Red::Entity>> App::StaticEntitySystem::GetTagged(Red::CName aTag)
{
    if (!m_ready)
        return {};

    std::shared_lock _(m_tagsLock);

    auto entityIDsEntry = m_entityIDsByTag.find(aTag);
    if (entityIDsEntry == m_entityIDsByTag.end())
        return {};

    Red::DynArray<Red::Handle<Red::Entity>> out;

    for (const auto& entityID : entityIDsEntry.value())
    {
        if (auto entity = GetEntity(entityID))
        {
            out.PushBack(entity);
        }
    }

    return out;
}

void App::StaticEntitySystem::DespawnTagged(Red::CName aTag)
{
    if (!m_ready)
        return;

    Core::Set<Red::EntityID> entityIDs;

    {
        std::shared_lock _(m_tagsLock);

        auto entityIDsEntry = m_entityIDsByTag.find(aTag);
        if (entityIDsEntry == m_entityIDsByTag.end())
            return;

        entityIDs = entityIDsEntry.value();
    }

    for (const auto& entityID : entityIDs)
    {
        DespawnEntity(entityID);
    }
}

void App::StaticEntitySystem::AttachTagged(Red::CName aTag)
{
    if (!m_ready)
        return;

    Core::Set<Red::EntityID> entityIDs;

    {
        std::shared_lock _(m_tagsLock);

        auto entityIDsEntry = m_entityIDsByTag.find(aTag);
        if (entityIDsEntry == m_entityIDsByTag.end())
            return;

        entityIDs = entityIDsEntry.value();
    }

    for (const auto& entityID : entityIDs)
    {
        AttachEntity(entityID);
    }
}

void App::StaticEntitySystem::DetachTagged(Red::CName aTag)
{
    if (!m_ready)
        return;

    Core::Set<Red::EntityID> entityIDs;

    {
        std::shared_lock _(m_tagsLock);

        auto entityIDsEntry = m_entityIDsByTag.find(aTag);
        if (entityIDsEntry == m_entityIDsByTag.end())
            return;

        entityIDs = entityIDsEntry.value();
    }

    for (const auto& entityID : entityIDs)
    {
        DetachEntity(entityID);
    }
}

bool App::StaticEntitySystem::ValidateEntitySpec(const App::StaticEntitySpecPtr& aEntitySpec)
{
    return Red::ResourceDepot::Get()->ResourceExists(aEntitySpec->templatePath.path);
}
