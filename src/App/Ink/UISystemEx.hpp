#pragma once

#include "Red/InkSystem.hpp"

namespace App
{
struct UISystemEx : Red::UISystem
{
    Red::DynArray<Red::Handle<Red::inkLayer>> GetLayers()
    {
        if (auto system = Red::InkSystem::Get())
        {
            return system->GetLayers();
        }

        return {};
    }

    Red::DynArray<Red::Handle<Red::inkVirtualWindow>> GetVirtualWindows()
    {
        Red::DynArray<Red::Handle<Red::inkVirtualWindow>> windows;

        if (auto system = Red::InkSystem::Get())
        {
            for (const auto& layer : system->GetLayers())
            {
                windows.PushBack(layer->window);
            }
        }

        return windows;
    }
};
}

RTTI_EXPAND_CLASS(App::UISystemEx, Red::UISystem, {
    RTTI_METHOD(GetLayers);
    RTTI_METHOD(GetVirtualWindows);
});
