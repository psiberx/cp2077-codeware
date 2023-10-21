#pragma once

namespace App
{
struct ComponentEx : Red::IComponent
{
    bool ChangeResource(Red::ResourceAsyncReference<> aReference, Red::Optional<bool> aWait);
    bool LoadResource(Red::Optional<bool> aWait);
    bool ChangeAppearance(Red::CName aName);
    bool LoadAppearance();
};
}

RTTI_EXPAND_CLASS(Red::IComponent, App::ComponentEx, {
    RTTI_METHOD(ChangeResource);
    RTTI_METHOD(LoadResource);
    RTTI_METHOD(ChangeAppearance);
    RTTI_METHOD(LoadAppearance);
});
