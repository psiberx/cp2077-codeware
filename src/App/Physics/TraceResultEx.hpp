#pragma once

#include "Red/Physics.hpp"

namespace App
{
struct TraceResultEx : Red::TraceResult
{
    uint32_t GetProxyID()
    {
        return Raw::PhysicsTraceResult::ResultID::Ref(this);
    }

    uint32_t GetActorIndex()
    {
        return Raw::PhysicsTraceResult::ActorIndex::Ref(this);
    }

    int32_t GetShapeIndex()
    {
        return Raw::PhysicsTraceResult::ShapeIndex::Ref(this);
    }

    Red::Handle<Red::ISerializable> GetHitObject()
    {
        auto& resultID = Raw::PhysicsTraceResult::ResultID::Ref(this);

        for (uint32_t i = 0; i < 2; ++i)
        {
            Red::Handle<Red::ISerializable> object;
            Raw::PhysicsTraceResult::GetHitObject(object, resultID, i);

            if (object)
            {
                return object;
            }
        }

        return {};
    }

    Red::Handle<Red::Entity> GetHitEntity()
    {
        auto& resultID = Raw::PhysicsTraceResult::ResultID::Ref(this);

        for (uint32_t i = 0; i < 2; ++i)
        {
            Red::Handle<Red::ISerializable> object;
            Raw::PhysicsTraceResult::GetHitObject(object, resultID, i);

            if (auto& entity = Red::Cast<Red::Entity>(object))
            {
                return entity;
            }
        }

        return {};
    }
};
}

RTTI_EXPAND_CLASS(Red::TraceResult, App::TraceResultEx, {
    RTTI_METHOD(GetProxyID);
    RTTI_METHOD(GetActorIndex);
    RTTI_METHOD(GetShapeIndex);
    RTTI_METHOD(GetHitObject);
    RTTI_METHOD(GetHitEntity);
});
