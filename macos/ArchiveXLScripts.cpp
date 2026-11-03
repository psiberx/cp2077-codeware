// Fallback stand-in for the ArchiveXL script class (listed in NOT_YET.md).
//
// The ArchiveXL plugin ported from source (cp2077-archive-xl-macos) registers the real `ArchiveXL` class, and in a session with that plugin this
// file registers nothing (a class is never registered twice, see MacSupport.cpp). In a session without it, for example with the closed
// NightCity Console ArchiveXL.dylib 1.26.1, which registers no script natives, the game has no `ArchiveXL` class and a script cache that
// calls ArchiveXL.Version() cannot link. This file then registers `public abstract native class ArchiveXL` with the five statics of
// ArchiveXL.Global.reds. EnableGarmentOffsets, DisableGarmentOffsets and GetBodyType are no-op stand-ins there: layered garments may clip
// and GetBodyType returns None.

#include "MacR13.hpp"

#include <atomic>
#include <cstdio>

namespace App
{
class ArchiveXLFacade : public Red::IScriptable
{
public:
    static constexpr auto InstalledVersion = "1.26.1";

    static Red::CString Version()
    {
        return InstalledVersion;
    }

    // Dotted versions compare numerically: Version() >= aVersion. Same rule as Codeware.Require.
    static bool Require(Red::CString& aVersion)
    {
        const auto installed = semver::from_string_noexcept(InstalledVersion);
        const auto requirement = semver::from_string_noexcept(aVersion.c_str());
        return installed.has_value() && requirement.has_value() ? installed.value() >= requirement.value() : false;
    }

    // Stand-in: no-op, logs one line, once.
    static void EnableGarmentOffsets()
    {
        LogGarmentOnce();
    }

    // Stand-in: no-op, logs one line, once.
    static void DisableGarmentOffsets()
    {
        LogGarmentOnce();
    }

    // Stand-in: returns None, logs once.
    static Red::CName GetBodyType(const Red::WeakHandle<Red::GameObject>& aPuppet)
    {
        static std::atomic<bool> s_logged{false};
        if (!s_logged.exchange(true))
        {
            std::fprintf(stderr, "[cw] ArchiveXL.GetBodyType not supported without the ArchiveXL plugin, returns None\n");
        }
        return {};
    }

    RTTI_IMPL_TYPEINFO(App::ArchiveXLFacade);

private:
    static void LogGarmentOnce()
    {
        static std::atomic<bool> s_logged{false};
        if (!s_logged.exchange(true))
        {
            std::fprintf(stderr, "[cw] ArchiveXL garment offsets not supported without the ArchiveXL plugin\n");
        }
    }
};
}

RTTI_DEFINE_CLASS(App::ArchiveXLFacade, "ArchiveXL", {
    RTTI_ABSTRACT();
    RTTI_METHOD(Version);
    RTTI_METHOD(Require);
    RTTI_METHOD(EnableGarmentOffsets);
    RTTI_METHOD(DisableGarmentOffsets);
    RTTI_METHOD(GetBodyType);
});

// codeware_registerNatives checks this before RunPending. The class lookup is by its script name, which
// equals the native name for ArchiveXL.
bool Mac::ArchiveXLClassExists()
{
    auto* rtti = RED4ext::CRTTISystem::Get();
    return rtti && rtti->GetClass(RED4ext::CName("ArchiveXL")) != nullptr;
}
