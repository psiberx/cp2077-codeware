#pragma once

namespace App
{
struct inkWidgetReferenceEx : Red::inkWidgetReference
{
    void Set(const Red::Handle<Red::inkWidget>& aWidget)
    {
        widget = aWidget;
    }
};
}

RTTI_EXPAND_CLASS(App::inkWidgetReferenceEx, Red::inkWidgetReference, {
    RTTI_METHOD(Set);
});
