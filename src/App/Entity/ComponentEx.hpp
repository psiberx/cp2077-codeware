#pragma once

namespace App
{
struct ComponentEx : Red::IComponent
{
    bool ChangeAppearance(Red::CName aAppearance);
    bool LoadAppearance();
};
}

RTTI_EXPAND_CLASS(Red::IComponent, App::ComponentEx, {
    RTTI_METHOD(ChangeAppearance);
    RTTI_METHOD(LoadAppearance);
});
