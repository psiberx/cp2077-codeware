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
    ResourcePathRegistry(const std::filesystem::path& aPreloadPath = {});

#if defined(__APPLE__)
    // Calls of the shared ResourcePath::Create hook (whichever plugin owns it).
    [[nodiscard]] static uint64_t SharedHitCount();
#endif
    [[nodiscard]] std::string ResolvePath(Red::ResourcePath aPath);
    [[nodiscard]] std::string ResolvePathOrHash(Red::ResourcePath aPath);

    Red::ResourcePath RegisterPath(const std::string& aPathStr);
    void RegisterPath(Red::ResourcePath aPath, const std::string& aPathStr);

protected:
    struct SharedInstance
    {
        Red::SharedSpinLock m_lock;
        Core::Map<Red::ResourcePath, std::string> m_map;
        bool m_preloaded{false};
        bool m_initialized{false};
#if defined(__APPLE__)
        // R22. Both plugins share this instance and the first one to start owns the only ResourcePath::Create hook. Every call
        // counts here, so either plugin can tell that the hook is alive. The layout is the same in Codeware and ArchiveXL.
        std::atomic<uint64_t> m_hits{0};
#endif
    };

    void OnBootstrap() override;
#if defined(__APPLE__)
    static void OnCreatePath(uint64_t& aHash, const char* aData, uint32_t aSize);
#else
    static void OnCreatePath(Red::ResourcePath* aPath, Red::StringView* aPathStr);
#endif

    inline static SharedInstance* s_instance;
    inline static std::filesystem::path s_preloadPath;
};
}
