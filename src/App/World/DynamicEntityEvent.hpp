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
        , entityTag(aTag)
    {
    }

    DynamicEntityEventType eventType;
    Red::EntityID entityID;
    Red::CName entityTag;

    RTTI_IMPL_TYPEINFO(App::DynamicEntityEvent);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_ENUM(App::DynamicEntityEventType);

RTTI_DEFINE_CLASS(App::DynamicEntityEvent, {
    RTTI_GETTER(eventType);
    RTTI_GETTER(entityID);
    RTTI_GETTER(entityTag);
});
