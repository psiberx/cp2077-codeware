#include "ResourcePathRegistry.hpp"

App::ResourcePathRegistry::ResourcePathRegistry(const std::filesystem::path& aKnownHashesPath)
{
    if (std::filesystem::exists(aKnownHashesPath))
    {
        std::unique_lock _(s_lock);
        std::thread([aKnownHashesPath]() {
            LogInfo("[ResourcePathRegistry] Loading metadata...");

            std::ifstream f(aKnownHashesPath);
            {
                std::string pathStr;
                while (std::getline(f, pathStr))
                {
                    s_pathMap[Red::ResourcePath::HashSanitized(pathStr.data())] = std::move(pathStr);
                }
            }

            LogInfo("[ResourcePathRegistry] Loaded {} predefined hashes.", s_pathMap.size());
        }).detach();
    }
}

void App::ResourcePathRegistry::OnBootstrap()
{
    HookAfter<Raw::ResourcePath::Create>(&OnCreateResourcePath);
}

void App::ResourcePathRegistry::OnCreateResourcePath(Red::ResourcePath* aPath, const Red::StringView* aPathStr)
{
    if (aPathStr)
    {
        std::unique_lock _(s_lock);
        s_pathMap[*aPath] = {aPathStr->data, aPathStr->size};
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
