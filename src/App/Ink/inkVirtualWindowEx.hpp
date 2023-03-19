#pragma once

namespace App
{
struct inkVirtualWindowEx : Red::inkVirtualWindow
{
    Red::CName GetLayerName()
    {
        if (layerProxy)
        {
            if (auto layer = layerProxy->layer.Lock())
            {
                return layer->GetNativeType()->name;
            }
        }

        return {};
    }

    Red::WeakHandle<Red::inkIGameController> GetGameController()
    {
        if (layerProxy)
        {
            if (auto layer = layerProxy->layer.Lock())
            {
                if (layer->libraryItem)
                {
                    return layer->libraryItem->gameController;
                }
            }
        }

        return {};
    }

    Red::DynArray<Red::WeakHandle<Red::inkIGameController>> GetGameControllers()
    {
        Red::DynArray<Red::WeakHandle<Red::inkIGameController>> controllers;

        if (layerProxy)
        {
            if (auto layer = layerProxy->layer.Lock())
            {
                for (const auto& controller : layer->controllerProcessor->controllers)
                {
                    controllers.PushBack(controller);
                }
            }
        }

        return controllers;
    }
};
}

RTTI_EXPAND_CLASS(App::inkVirtualWindowEx, Red::inkVirtualWindow, {
    RTTI_METHOD(GetLayerName);
    RTTI_METHOD(GetGameController);
    RTTI_METHOD(GetGameControllers);
});
