#pragma once

namespace App
{
struct inkWorldWidgetInfosEx : Red::inkWorldWidgetInfos
{
    Red::Handle<Red::IComponent> GetComponent()
    {
        auto& wrapper = *reinterpret_cast<Red::SharedPtr<Red::worlduiWorldLayerWidget>*>(&unk40);

        if (!wrapper)
            return {};

        return *reinterpret_cast<Red::WeakHandle<Red::IComponent>*>(&wrapper->unk08);
    }
};
}

RTTI_EXPAND_CLASS(Red::inkWorldWidgetInfos, App::inkWorldWidgetInfosEx, {
    RTTI_METHOD(GetComponent);
});
