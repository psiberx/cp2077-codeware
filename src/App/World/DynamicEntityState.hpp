#pragma once

#include "DynamicEntitySpec.hpp"

namespace App
{
struct DynamicEntityState : Red::IScriptable
{
    DynamicEntityState() = default;

    DynamicEntityState(Red::EntityID aEntityId, Red::Handle<DynamicEntitySpec> entitySpec)
        : entityID(aEntityId)
        , entitySpec(std::move(entitySpec))
        , entityStub(nullptr)
    {
    }

    void TakeoveStub(Red::EntityStubToken& aToken)
    {
        entityStub = aToken.ExtractStub();
    }

    Red::EntityID entityID;
    Red::Handle<DynamicEntitySpec> entitySpec;
    Red::EntityStub* entityStub;

    RTTI_IMPL_TYPEINFO(App::DynamicEntityState);
    RTTI_IMPL_ALLOCATOR(Red::Memory::RTTIAllocator);
};

using DynamicEntityStatePtr = Red::Handle<DynamicEntityState>;
}

RTTI_DEFINE_CLASS(App::DynamicEntityState, {
    RTTI_PERSISTENT(entityID);
    RTTI_PERSISTENT(entitySpec);
});
