#include "ResourcePathRegistry.hpp"

void App::ResourcePathRegistry::OnBootstrap()
{
    HookAfter<Raw::ResourcePath::Create>(&OnCreateResourcePath);
}

void App::ResourcePathRegistry::OnCreateResourcePath(Red::ResourcePath* aPath, const Red::StringView* aPathStr)
{
    if (aPathStr)
    {
        std::unique_lock _(s_lock);
        std::string_view pathStr(aPathStr->data, aPathStr->size);
        s_pathMap[*aPath] = pathStr;
        s_widlcardMap[*aPath] = pathStr.find('*');
    }
}

std::string_view App::ResourcePathRegistry::GetPath(Red::ResourcePath aPath) const
{
    if (!aPath)
        return {};

    std::shared_lock _(s_lock);
    const auto& it = s_pathMap.find(aPath);

    if (it == s_pathMap.end())
        return {};

    return it.value();
}

bool App::ResourcePathRegistry::IsWildcard(Red::ResourcePath aPath) const
{
    std::shared_lock _(s_lock);
    return s_widlcardMap.contains(aPath);
}
