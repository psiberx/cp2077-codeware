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
        : type(aType)
        , entityID(aEntityId)
        , tag(aTag)
    {
    }

    DynamicEntityEventType type;
    Red::EntityID entityID;
    Red::CName tag;

    RTTI_IMPL_TYPEINFO(App::DynamicEntityEvent);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_ENUM(App::DynamicEntityEventType);

RTTI_DEFINE_CLASS(App::DynamicEntityEvent, {
    RTTI_GETTER(type);
    RTTI_GETTER(entityID);
    RTTI_GETTER(tag);
});
