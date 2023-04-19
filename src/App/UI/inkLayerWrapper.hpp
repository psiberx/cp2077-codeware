#pragma once

namespace App
{
struct inkLayerWrapper : Red::IScriptable
{
    inkLayerWrapper()
        : layer(nullptr)
    {
    }

    inkLayerWrapper(Red::Handle<Red::inkLayer> aLayer)
        : layer(std::move(aLayer))
    {
    }

    inkLayerWrapper(const inkLayerWrapper&) = default;
    inkLayerWrapper(inkLayerWrapper&&) = default;

    Red::CName GetLayerName()
    {
        if (layer)
        {
            return layer->GetNativeType()->name;
        }

        return {};
    }

    Red::WeakHandle<Red::inkVirtualWindow> GetVirtualWindow()
    {
        if (layer)
        {
            return layer->window;
        }

        return {};
    }

    Red::WeakHandle<Red::inkIGameController> GetGameController()
    {
        if (layer && layer->libraryItem)
        {
            return layer->libraryItem->gameController;
        }

        return {};
    }

    Red::DynArray<Red::WeakHandle<Red::inkIGameController>> GetGameControllers()
    {
        Red::DynArray<Red::WeakHandle<Red::inkIGameController>> controllers;

        if (layer)
        {
            for (const auto& controller : layer->controllerProcessor->controllers)
            {
                controllers.PushBack(controller);
            }
        }

        return controllers;
    }

    Red::Handle<Red::inkLayer> layer;

    RTTI_IMPL_TYPEINFO(App::inkLayerWrapper);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::inkLayerWrapper, {
    RTTI_METHOD(GetLayerName);
    RTTI_METHOD(GetVirtualWindow);
    RTTI_METHOD(GetGameController);
    RTTI_METHOD(GetGameControllers);
});
