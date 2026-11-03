#pragma once

namespace App
{
struct inkWidgetLibraryEx : Red::inkWidgetLibraryResourceWrapper
{
    static Red::inkWidgetLibraryResourceWrapper Create(Red::ResourcePath aPath)
    {
        return {aPath};
    }

    void SetPath(Red::RaRef<Red::inkWidgetLibraryResource>& aPath)
    {
        library = aPath;
    }
};
}

RTTI_EXPAND_CLASS(Red::inkWidgetLibraryResourceWrapper, App::inkWidgetLibraryEx, {
    RTTI_METHOD(Create);
    RTTI_METHOD(SetPath);
});
