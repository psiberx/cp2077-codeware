#pragma once

namespace App
{
struct ComponentEx : Red::IComponent
{
    bool ChangeResource(const Red::ResourceAsyncReference<>& aReference, Red::Optional<bool> aWait);
    bool LoadResource(Red::Optional<bool> aWait);
    bool ChangeAppearance(Red::CName aName, Red::Optional<bool> aWait);
    bool LoadAppearance(Red::Optional<bool> aWait);
    bool RefreshAppearance();
};
}

RTTI_EXPAND_CLASS(Red::IComponent, App::ComponentEx, {
    RTTI_METHOD(ChangeResource);
    RTTI_METHOD(LoadResource);
    RTTI_METHOD(ChangeAppearance);
    RTTI_METHOD(LoadAppearance);
    RTTI_METHOD(RefreshAppearance);
});
