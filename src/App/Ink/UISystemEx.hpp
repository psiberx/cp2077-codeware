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

    Red::Handle<Red::inkVirtualWindow> GetVirtualWindow(Red::CName aLayerName)
    {
        if (auto system = Red::InkSystem::Get())
        {
            for (const auto& layer : system->GetLayers())
            {
                if (layer->GetNativeType()->name == aLayerName)
                {
                    return layer->window;
                }
            }
        }

        return {};
    }
};
}

RTTI_EXPAND_CLASS(App::UISystemEx, Red::UISystem, {
    RTTI_METHOD(GetLayers);
    RTTI_METHOD(GetVirtualWindows);
    RTTI_METHOD(GetVirtualWindow);
});
