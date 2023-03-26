#pragma once

namespace App
{
struct DynamicEntitySpec : Red::IScriptable
{
    DynamicEntitySpec()
        : recordID()
        , templatePath()
        , templateHash()
        , appearanceName()
        , position()
        , orientation{0, 0, 0, 1}
        , persistState()
        , persistSpawn()
        , alwaysSpawned()
        , spawnInView(true)
        , tags()
        , active(true)
    {
    }

    [[nodiscard]] inline bool IsValid() const
    {
        return IsRecord() || IsTemplate();
    }

    [[nodiscard]] inline bool IsRecord() const
    {
        return recordID.IsValid();
    }

    [[nodiscard]] inline bool IsTemplate() const
    {
        return !IsRecord() && !templatePath.path.IsEmpty();
    }

    void PrepareForSaving()
    {
        templateHash = templatePath.path;
    }

    void PrepareForRestoring()
    {
        templatePath.path = templateHash;
    }

    Red::TweakDBID recordID;
    Red::RaRef<> templatePath;
    uint64_t templateHash;
    Red::CName appearanceName;
    Red::Vector4 position;
    Red::Quaternion orientation;
    bool persistState;
    bool persistSpawn;
    bool alwaysSpawned;
    bool spawnInView;
    Red::DynArray<Red::CName> tags;
    bool active;

    RTTI_IMPL_TYPEINFO(App::DynamicEntitySpec);
    RTTI_IMPL_ALLOCATOR(Red::Memory::RTTIAllocator);
};

using DynamicEntitySpecPtr = Red::Handle<DynamicEntitySpec>;
}

RTTI_DEFINE_CLASS(App::DynamicEntitySpec, {
    RTTI_METHOD(IsValid);
    RTTI_PERSISTENT(recordID);
    RTTI_PROPERTY(templatePath);
    RTTI_PERSISTENT(templateHash);
    RTTI_PERSISTENT(appearanceName);
    RTTI_PERSISTENT(position);
    RTTI_PERSISTENT(orientation);
    RTTI_PERSISTENT(persistState);
    RTTI_PERSISTENT(persistSpawn);
    RTTI_PERSISTENT(alwaysSpawned);
    RTTI_PERSISTENT(spawnInView);
    RTTI_PERSISTENT(tags);
    RTTI_PERSISTENT(active);
});
