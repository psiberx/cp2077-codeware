#pragma once

#include "Red/WorldNode.hpp"
#include <RED4ext/Scripting/Natives/Generated/world/CollisionNode.hpp>
#include <RED4ext/Scripting/Natives/Generated/world/CollisionNodeInstance.hpp>

namespace App
{
struct CollisionNodeInstanceEx : Red::worldCollisionNodeInstance
{
    [[nodiscard]] uint32_t GetPrimaryPhysicsProxyID() const
    {
        return Raw::WorldCollisionNodeInstance::PrimaryProxyID::Ref(this);
    }

    [[nodiscard]] uint32_t GetOverflowPhysicsProxyID() const
    {
        return Raw::WorldCollisionNodeInstance::OverflowProxyID::Ref(this);
    }

    [[nodiscard]] bool HasOverflowPhysicsProxy() const
    {
        return GetOverflowPhysicsProxyID() != 0;
    }

    [[nodiscard]] int32_t GetCollisionActorCount() const
    {
        auto node = Raw::WorldNodeInstance::Node::Ref(this);
        if (!node)
            return 0;

        if (auto collisionNode = Red::Cast<Red::worldCollisionNode>(node))
            return static_cast<int32_t>(collisionNode->numActors);

        return 0;
    }

    [[nodiscard]] int32_t GetCollisionSplitIndex() const
    {
        const int32_t count = GetCollisionActorCount();
        return HasOverflowPhysicsProxy() ? count / 2 : count;
    }

    [[nodiscard]] int32_t ResolveActorIndex(uint32_t aHitProxyID, uint32_t aLocalActorIndex) const
    {
        if (aHitProxyID == GetPrimaryPhysicsProxyID())
            return static_cast<int32_t>(aLocalActorIndex);

        if (HasOverflowPhysicsProxy() && aHitProxyID == GetOverflowPhysicsProxyID())
            return GetCollisionSplitIndex() + static_cast<int32_t>(aLocalActorIndex);

        return -1;
    }
};
}

RTTI_EXPAND_CLASS(Red::worldCollisionNodeInstance, App::CollisionNodeInstanceEx, {
    RTTI_METHOD(GetPrimaryPhysicsProxyID);
    RTTI_METHOD(GetOverflowPhysicsProxyID);
    RTTI_METHOD(HasOverflowPhysicsProxy);
    RTTI_METHOD(GetCollisionActorCount);
    RTTI_METHOD(GetCollisionSplitIndex);
    RTTI_METHOD(ResolveActorIndex);
});
