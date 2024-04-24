#pragma once

#include "Red/Physics.hpp"

namespace App
{
struct TraceResultEx : Red::TraceResult
{
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
    RTTI_METHOD(GetHitObject);
    RTTI_METHOD(GetHitEntity);
});
