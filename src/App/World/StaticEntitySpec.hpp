#pragma once

namespace App
{
struct StaticEntitySpec : Red::IScriptable
{
    StaticEntitySpec()
        : templatePath()
        , appearanceName()
        , position()
        , orientation{0, 0, 0, 1}
        , tags()
        , attached(true)
    {
    }

    StaticEntitySpec(const StaticEntitySpec& aOther) = default;
    StaticEntitySpec(StaticEntitySpec&&) = default;

    Red::RaRef<> templatePath;
    Red::CName appearanceName;
    Red::Vector4 position;
    Red::Quaternion orientation;
    Red::DynArray<Red::CName> tags;
    bool attached;

    RTTI_IMPL_TYPEINFO(App::StaticEntitySpec);
    RTTI_IMPL_ALLOCATOR();
};

using StaticEntitySpecPtr = Red::Handle<StaticEntitySpec>;
}

RTTI_DEFINE_CLASS(App::StaticEntitySpec, {
    RTTI_PROPERTY(templatePath);
    RTTI_PROPERTY(appearanceName);
    RTTI_PROPERTY(position);
    RTTI_PROPERTY(orientation);
    RTTI_PROPERTY(tags);
    RTTI_PROPERTY(attached);
});
