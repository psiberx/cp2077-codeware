#pragma once

#include "App/World/DynamicEntitySpec.hpp"

namespace App
{
struct DynamicEntityState : Red::IScriptable
{
    DynamicEntityState() = default;

    DynamicEntityState(Red::EntityID aEntityId, Red::Handle<DynamicEntitySpec> aEntitySpec)
        : entityID(aEntityId)
        , entitySpec(std::move(aEntitySpec))
        , deleted(false)
    {
    }

    void AcquireStub(Red::EntityStubTokenPtr& aToken)
    {
        std::unique_lock _(entityLock);
        entityStub = aToken->ExtractStub();
    }

    Red::UniquePtr<Red::EntityStub> ExtractStub()
    {
        std::unique_lock _(entityLock);
        return std::move(entityStub);
    }

    Red::EntityID entityID; // Never changes after state creation or restoration
    Red::Handle<DynamicEntitySpec> entitySpec;
    Red::UniquePtr<Red::EntityStub> entityStub;
    Red::SharedSpinLock entityLock; // For stub, active and deleted statuses
    bool deleted;

    RTTI_IMPL_TYPEINFO(App::DynamicEntityState);
    RTTI_IMPL_ALLOCATOR();
};

using DynamicEntityStatePtr = Red::Handle<DynamicEntityState>;
}

RTTI_DEFINE_CLASS(App::DynamicEntityState, {
    RTTI_PERSISTENT(entityID);
    RTTI_PERSISTENT(entitySpec);
});
