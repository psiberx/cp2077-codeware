#pragma once

namespace App
{
struct ComponentEx : Red::IComponent
{
    bool LoadAppearance();
};
}

RTTI_EXPAND_CLASS(Red::IComponent, App::ComponentEx, {
    RTTI_METHOD(LoadAppearance);
});
