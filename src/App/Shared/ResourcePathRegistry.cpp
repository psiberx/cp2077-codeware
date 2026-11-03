#include "ResourcePathRegistry.hpp"
#include "App/Project.hpp"
#include "Red/SharedStorage.hpp"
#if defined(__APPLE__)
#include "MacEngine.hpp"
#include "MacDiag.hpp"
#endif

namespace
{
constexpr auto SharedName = Red::CName("ResourcePathRegistryV3" BUILD_SUFFIX);
}

App::ResourcePathRegistry::ResourcePathRegistry(const std::filesystem::path& aPreloadPath)
{
    s_instance = Red::AcquireSharedInstance<SharedName, SharedInstance>();
    s_preloadPath = aPreloadPath;
}

void App::ResourcePathRegistry::OnBootstrap()
{
    std::unique_lock lock(s_instance->m_lock);

    if (!s_instance->m_initialized)
    {
        s_instance->m_initialized = true;
        s_instance->m_map.reserve(400000);

#if defined(__APPLE__)
        const bool hooked = HookAfter<Raw::ResourcePath::Create>(&OnCreatePath);
        MAC_DIAG_UNLESS(hooked, "[cw] hook %s ResourcePathRegistry ResourcePath::Create target=%p\n", hooked ? "installed" : "FAILED",
                     reinterpret_cast<void*>(Raw::ResourcePath::Create.GetOriginalAddress()));
#else
        HookAfter<Raw::ResourcePath::Create>(&OnCreatePath);
#endif
    }

    if (!s_instance->m_preloaded && !s_preloadPath.empty() && std::filesystem::exists(s_preloadPath))
    {
        s_instance->m_preloaded = true;

        std::thread([lock = std::move(lock)]() {
            LogInfo("[ResourcePathRegistry] Loading metadata...");

            std::ifstream f(s_preloadPath);
            std::string s;
            while (std::getline(f, s))
            {
                s_instance->m_map[Red::ResourcePath::HashSanitized(s.data())] = std::move(s);
            }

            LogInfo("[ResourcePathRegistry] Loaded {} predefined hashes.", s_instance->m_map.size());
        }).detach();
    }
}

#if defined(__APPLE__)
uint64_t App::ResourcePathRegistry::SharedHitCount()
{
    return s_instance ? s_instance->m_hits.load(std::memory_order_relaxed) : 0;
}

// MAC-NOT-YET: the ResourcePath::Create hook (0x21C90A4) must chain with ArchiveXL's own hook on the same function: the old ArchiveXL 1.26.1 Mac build uses the Windows signature (ResourcePath*, StringView*) and crashes in its first call once the offset is on the allowlist (r19h), so the launcher parks ArchiveXL.dylib until the ported ArchiveXL (Stage 3, signature uint64_t(const char*, uint32_t)) is tested chained with this hook.
void App::ResourcePathRegistry::OnCreatePath(uint64_t& aHash, const char* aData, uint32_t aSize)
{
    if (aData && aSize > 0 && aHash)
    {
        static auto& counter = Mac::HookCount("ResourcePath_Create");
        Mac::Hit(counter);
        s_instance->m_hits.fetch_add(1, std::memory_order_relaxed);

        std::scoped_lock _(s_instance->m_lock);
        s_instance->m_map[Red::ResourcePath(aHash)] = {aData, aSize};
    }
}
#else
void App::ResourcePathRegistry::OnCreatePath(Red::ResourcePath* aPath, Red::StringView* aPathStr)
{
    if (aPathStr && *aPathStr)
    {
        std::scoped_lock _(s_instance->m_lock);
        s_instance->m_map[*aPath] = {aPathStr->Data(), aPathStr->Length()};
    }
}
#endif

std::string App::ResourcePathRegistry::ResolvePath(Red::ResourcePath aPath)
{
    if (!aPath)
        return {};

    std::shared_lock _(s_instance->m_lock);
    const auto& it = s_instance->m_map.find(aPath);

    if (it == s_instance->m_map.end())
        return {};

    return it.value();
}

std::string App::ResourcePathRegistry::ResolvePathOrHash(Red::ResourcePath aPath)
{
    auto str = ResolvePath(aPath);

    if (str.empty())
    {
        str = std::to_string(aPath.hash);
    }

    return str;
}

Red::ResourcePath App::ResourcePathRegistry::RegisterPath(const std::string& aPathStr)
{
    if (aPathStr.empty())
        return {};

    auto path = Red::ResourcePath(aPathStr.data());

    RegisterPath(path, aPathStr);

    return path;
}

void App::ResourcePathRegistry::RegisterPath(Red::ResourcePath aPath, const std::string& aPathStr)
{
    if (!aPath)
        return;

    {
        std::shared_lock _(s_instance->m_lock);
        if (s_instance->m_map.contains(aPath))
            return;
    }

    {
        std::scoped_lock _(s_instance->m_lock);
        s_instance->m_map[aPath] = aPathStr;
    }
}
