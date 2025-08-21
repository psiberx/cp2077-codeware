#pragma once

namespace Red
{
struct RenderData
{
};

struct RenderDataPtr
{
    RenderData* data;
};

struct RenderProxy
{
    virtual ~RenderProxy() = 0;
};

struct HighlightParams
{
    bool seeThroughWalls; // 00
    uint8_t patternType;  // 01
    uint8_t fillIndex;    // 02
    uint8_t outlineIndex; // 03
    float opacity;        // 04
    bool forced;          // 08
};
}

namespace Raw::RenderData
{
constexpr auto Release = Core::RawFunc<
    /* addr = */ Red::AddressLib::RenderData_Release,
    /* type = */ void (*)(Red::RenderData* aPtr)>();
}

namespace Raw::RenderProxy
{
using Flags = Core::OffsetPtr<0x23, uint8_t>;

inline bool IsVisible(Red::RenderProxy* aProxy)
{
    return (Flags::Ref(aProxy) & 6) == 6;
}

constexpr auto SetVisibility = Core::RawFunc<
    /* addr = */ Red::AddressLib::RenderProxy_SetVisibility,
    /* type = */ void (*)(Red::RenderProxy* aProxy, bool aVisible)>();

constexpr auto UpdateVisibility = Core::RawFunc<
    /* addr = */ Red::AddressLib::RenderProxy_UpdateVisibility,
    /* type = */ void (*)(Red::RenderProxy* aProxy, bool aVisible)>();

constexpr auto SetHighlightParams = Core::RawFunc<
    /* addr = */ Red::AddressLib::RenderProxy_SetHighlightParams,
    /* type = */ uint8_t (*)(Red::RenderProxy* aProxy, const Red::HighlightParams& aParams)>();

constexpr auto SetScanningState = Core::RawFunc<
    /* addr = */ Red::AddressLib::RenderProxy_SetScanningState,
    /* type = */ uint8_t (*)(Red::RenderProxy* aProxy, Red::rendPostFx_ScanningState aState)>();

constexpr auto SetMaterialOverride = Core::RawFunc<
    /* addr = */ Red::AddressLib::RenderProxy_SetMaterialOverride,
    /* type = */ void (*)(Red::RenderProxy* aProxy, const Red::RenderDataPtr& aMaterial,
                          const Red::RenderDataPtr& a3, bool aReplace)>();
}

namespace Raw::VisionModeSystem
{
constexpr auto SetBraindanceMode = Core::RawFunc<
    /* addr = */ Red::AddressLib::VisionModeSystem_SetBraindanceMode,
    /* type = */ void (*)(void* aSystem, uint32_t aMode)>();
}
