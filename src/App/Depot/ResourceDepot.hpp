#pragma once

namespace App
{
struct ResourceDepot : Red::IScriptable
{
    bool IsArchiveExists(const Red::CString& aPath)
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

    bool IsResourceExists(const Red::RaRef<>& aRef)
    {
        const auto depot = Red::ResourceDepot::Get();

        return depot && depot->ResourceExists(aRef.path);
    }

    static Red::Handle<ResourceDepot> Get()
    {
        return Red::MakeHandle<ResourceDepot>();
    }

    RTTI_IMPL_TYPEINFO(App::ResourceDepot);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::ResourceDepot, {
    RTTI_METHOD(IsArchiveExists);
    RTTI_METHOD(IsResourceExists);
});

RTTI_EXPAND_CLASS(Red::ScriptGameInstance, {
    RTTI_METHOD_FQN(App::ResourceDepot::Get, "GetResourceDepot");
});
