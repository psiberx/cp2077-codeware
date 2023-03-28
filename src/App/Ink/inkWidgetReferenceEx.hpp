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

RTTI_EXPAND_CLASS(Red::inkWidgetReference, App::inkWidgetReferenceEx, {
    RTTI_METHOD(Set);
});
