#pragma once

namespace App
{
struct inkWidgetLibraryEx : Red::inkWidgetLibraryResourceWrapper
{
    void SetPath(Red::RaRef<Red::inkWidgetLibraryResource>& aPath)
    {
        library = aPath;
    }
};
}

RTTI_EXPAND_CLASS(Red::inkWidgetLibraryResourceWrapper, App::inkWidgetLibraryEx, {
    RTTI_METHOD(SetPath);
});
