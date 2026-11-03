#pragma once

#include "App/UI/inkLayerWrapper.hpp"
#include "Red/InkSystem.hpp"

#if defined(__APPLE__)
#include <string>
void cw_clipboard_get(std::string& aOut);
void cw_clipboard_set(const char* aText);
#endif

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

    Red::DynArray<Red::WeakHandle<Red::inkIGameController>> GetWorldWidgets()
    {
        if (auto system = Red::InkSystem::Get())
        {
            for (const auto& layer : system->GetLayers())
            {
                if (const auto& worldLayer = Red::Cast<Red::inkWorldLayer>(layer))
                {
                    Red::DynArray<Red::WeakHandle<Red::inkIGameController>> controllers;

                    for (const auto& component : worldLayer->components)
                    {
                        auto window = component->GetWindow();
                        if (window)
                        {
                            controllers.PushBack(component->GetGameController());
                        }
                    }

                    return controllers;
                }
            }
        }

        return {};
    }

    Red::CString GetClipboardText()
    {
        std::string text;
#if defined(__APPLE__)
        cw_clipboard_get(text);
#else
        clip::get_text(text);
#endif
        return text;
    }

    void SetClipboardText(const Red::CString& aText)
    {
#if defined(__APPLE__)
        cw_clipboard_set(aText.c_str());
#else
        clip::set_text(aText.c_str());
#endif
    }

    RTTI_IMPL_TYPEINFO(App::inkSystem);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::inkSystem, {
    RTTI_METHOD(GetLayers);
    RTTI_METHOD(GetLayer);
    RTTI_METHOD(GetWorldWidgets);
    RTTI_METHOD(GetClipboardText);
    RTTI_METHOD(SetClipboardText);
});
