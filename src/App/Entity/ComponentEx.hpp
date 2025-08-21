#pragma once

namespace App
{
struct ComponentEx : Red::IComponent
{
    bool ChangeResource(const Red::ResourceAsyncReference<>& aReference, Red::Optional<bool> aWait);
    bool ChangeAppearance(Red::CName aName, Red::Optional<bool> aWait);
    bool LoadAppearance(Red::Optional<bool> aWait);
    bool RefreshAppearance();
    void ResetMaterialCache();
};
}

RTTI_EXPAND_CLASS(Red::IComponent, App::ComponentEx, {
    RTTI_PROPERTY(appearanceName);
    RTTI_PROPERTY(appearancePath);
    RTTI_METHOD(ChangeResource);
    RTTI_METHOD(ChangeAppearance);
    RTTI_METHOD(LoadAppearance);
    RTTI_METHOD(RefreshAppearance);
    RTTI_METHOD(ResetMaterialCache);
});
