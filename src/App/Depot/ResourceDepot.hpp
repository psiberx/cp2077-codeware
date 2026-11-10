#pragma once

#include "App/Depot/ResourceToken.hpp"
#include "Red/ResourceBank.hpp"

namespace App
{
struct ResourceDepot : Red::IScriptable
{
    bool ArchiveExists(const Red::CString& aPath)
    {
        const auto depot = Red::ResourceDepot::Get();

        if (depot)
        {
            for (const auto& archiveGroup : depot->groups)
            {
                if (archiveGroup.scope == Red::ArchiveScope::Mod)
                {
                    for (const auto& archive : archiveGroup.archives)
                    {
                        auto archivePath = std::filesystem::path(archive.path.c_str());
                        if (archivePath.filename() == aPath.c_str())
                            return true;
                    }
                }
            }
        }

        return false;
    }

    bool ResourceExists(const Red::ResourceAsyncReference<>& aRef)
    {
        auto depot = Red::ResourceDepot::Get();

        return depot && depot->ResourceExists(aRef.path);
    }

    [[nodiscard]] Red::Handle<ResourceTokenWrapper> LoadResource(const Red::ResourceAsyncReference<>& aRef) const
    {
        auto loader = Red::ResourceLoader::Get();

        return Red::MakeHandle<ResourceTokenWrapper>(loader->LoadAsync({.path = aRef.path, .updateCache = true}));
    }

    [[nodiscard]] Red::Handle<ResourceTokenWrapper> LoadReference(const Red::ResourceReference<>& aRef) const
    {
        return Red::MakeHandle<ResourceTokenWrapper>(aRef.token);
    }

    void RemoveResourceFromCache(const Red::ResourceAsyncReference<>& aRef)
    {
        auto loader = Red::ResourceLoader::Get();

        std::unique_lock lock(loader->tokenLock);

        Red::Handle<Red::CResource> resource;
        Raw::ResourceBank::ForgetResource(loader->bank, resource, aRef.path);
    }

    static Red::Handle<ResourceDepot> Get()
    {
        static const auto s_instance = Red::MakeHandle<ResourceDepot>();
        return s_instance;
    }

    RTTI_IMPL_TYPEINFO(App::ResourceDepot);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::ResourceDepot, {
    RTTI_METHOD(ArchiveExists);
    RTTI_METHOD(ResourceExists);
    RTTI_METHOD(LoadResource);
    RTTI_METHOD(LoadReference);
    RTTI_METHOD(RemoveResourceFromCache);
});

RTTI_EXPAND_CLASS(Red::ScriptGameInstance, {
    RTTI_METHOD_FQN(App::ResourceDepot::Get, "GetResourceDepot");
});
