#pragma once

#include "Core/Foundation/Feature.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Core/Logging/LoggingAgent.hpp"
#include "Red/ResourcePath.hpp"

namespace App
{
class ResourcePathRegistry
    : public Core::Feature
    , public Core::LoggingAgent
    , public Core::HookingAgent
{
public:
    ResourcePathRegistry(const std::filesystem::path& aKnownHashesPath);

    [[nodiscard]] std::string_view GetPath(Red::ResourcePath aPath) const;

protected:
    void OnBootstrap() override;

    static void OnCreateResourcePath(Red::ResourcePath* aPath, const Red::StringView* aPathStr);

    inline static std::shared_mutex s_lock;
    inline static Core::Map<Red::ResourcePath, std::string> s_pathMap;
};
}
