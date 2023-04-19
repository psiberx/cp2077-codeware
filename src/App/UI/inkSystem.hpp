#pragma once

#include "App/UI/inkLayerWrapper.hpp"
#include "Red/InkSystem.hpp"

namespace App
{
struct inkSystem : Red::IGameSystem
{
    Red::DynArray<Red::Handle<App::inkLayerWrapper>> GetLayers()
    {
        Red::DynArray<Red::Handle<App::inkLayerWrapper>> layers;

        if (auto system = Red::InkSystem::Get())
        {
            for (const auto& layer : system->GetLayers())
            {
                layers.PushBack(Red::MakeHandle<inkLayerWrapper>(layer));
            }
        }

        return layers;
    }

    Red::Handle<App::inkLayerWrapper> GetLayer(Red::CName aLayerName)
    {
        if (auto system = Red::InkSystem::Get())
        {
            for (const auto& layer : system->GetLayers())
            {
                if (layer->GetNativeType()->name == aLayerName)
                {
                    return Red::MakeHandle<inkLayerWrapper>(layer);
                }
            }
        }

        return {};
    }

    RTTI_IMPL_TYPEINFO(App::inkSystem);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::inkSystem, {
    RTTI_METHOD(GetLayers);
    RTTI_METHOD(GetLayer);
});
