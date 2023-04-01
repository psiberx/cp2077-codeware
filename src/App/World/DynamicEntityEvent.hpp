#pragma once

namespace App
{
enum class DynamicEntityEventType : uint32_t
{
    Created,
    Deleted,
    Spawned,
    Despawned,
    Dead,
};

struct DynamicEntityEvent : Red::IScriptable
{
    DynamicEntityEvent() = default;

    DynamicEntityEvent(DynamicEntityEventType aType, const Red::EntityID& aEntityId, Red::CName aTag)
        : eventType(aType)
        , entityID(aEntityId)
        , tag(aTag)
    {
    }

    auto GetEventType() const
    {
        return eventType;
    }

    auto GetEntityID() const
    {
        return entityID;
    }

    auto GetTag() const
    {
        return tag;
    }

    DynamicEntityEventType eventType;
    Red::EntityID entityID;
    Red::CName tag;

    RTTI_IMPL_TYPEINFO(App::DynamicEntityEvent);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_ENUM(App::DynamicEntityEventType);

RTTI_DEFINE_CLASS(App::DynamicEntityEvent, {
    RTTI_METHOD(GetEventType, "GetType");
    RTTI_METHOD(GetEntityID);
    RTTI_METHOD(GetTag);
});
