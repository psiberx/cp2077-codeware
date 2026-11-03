#pragma once

#include "Red/Rendering.hpp"

namespace Raw::CMesh
{
constexpr auto GetAppearance = Core::RawFunc<
    /* addr = */ Red::AddressLib::CMesh_GetAppearance,
    /* type = */ Red::Handle<Red::mesh::MeshAppearance>& (*)(Red::CMesh* aMesh, Red::CName aAppearance)>();

constexpr auto FindAppearance = Core::RawFunc<
    /* addr = */ Red::AddressLib::CMesh_FindAppearance,
    /* type = */ Red::Handle<Red::mesh::MeshAppearance>& (*)(Red::CMesh* aMesh, Red::CName aAppearance)>();
}

namespace Raw::MeshAppearance
{
// Game 2.5: MeshAppearance_LoadMaterialSetupAsync 0x40AC88 uses 0xA0 (0x40ACEE), 0x98 (0x40AD09), 0x48 (0x40AD1F),
// 0x90 (0x40AD30), 0x50 (0x40AD99); MeshAppearance_ReleaseReference 0x31C0F8 clears the map at 0x68 (keys size
// 0x74, values 0x78/0x84, flags 0x88: 0x31C178-0x31C192).
using MaterialData = Core::OffsetPtr<0x48, Red::RenderDataPtr>;
using Owner = Core::OffsetPtr<0x50, Red::CMesh*>;
using MaterialMap = Core::OffsetPtr<0x68, Red::Map<Red::CName, Red::Handle<Red::IMaterial>>>;
using MaterialJob = Core::OffsetPtr<0x90, Red::JobHandle>;
using MaterialLock = Core::OffsetPtr<0x98, Red::SharedSpinLock>;
using ForceCache = Core::OffsetPtr<0xA0, bool>;

#if defined(__APPLE__)
// Mac ABI (R21): the Handle comes back through x8 and a3 moves to w1. LoadMaterialSetupAsync keeps the Windows call shape.
constexpr auto LoadMaterialSetupAsyncNative = Core::RawFunc<
    /* addr = */ Red::AddressLib::MeshAppearance_LoadMaterialSetupAsync,
    /* type = */ Red::Handle<Red::mesh::MeshAppearance> (*)(Red::mesh::MeshAppearance* aAppearance, uint8_t a3)>();

struct LoadMaterialSetupAsyncFn
{
    void operator()(Red::mesh::MeshAppearance& aAppearance, Red::Handle<Red::mesh::MeshAppearance>& aOut, uint8_t a3) const
    {
        aOut = LoadMaterialSetupAsyncNative(&aAppearance, a3);
    }
};
inline constexpr LoadMaterialSetupAsyncFn LoadMaterialSetupAsync{};
#else
constexpr auto LoadMaterialSetupAsync = Core::RawFunc<
    /* addr = */ Red::AddressLib::MeshAppearance_LoadMaterialSetupAsync,
    /* type = */ void (*)(Red::mesh::MeshAppearance& aAppearance, Red::Handle<Red::mesh::MeshAppearance>& aOut,
                          uint8_t a3)>();
#endif
}

namespace Raw::MeshComponent
{
// Mac (R21, checked against the game by body for entMeshComponent and entSkinnedMeshComponent): LoadResource 0x268, RefreshAppearance
// 0x288, both Windows + 8. The value LoadResource returns is undefined on both sides; Codeware ignores it.
// Game 2.5: entMeshComponent slots 0x260 (0x299AE78) and 0x280 (0x715078) have the same code as on 2.31.
constexpr auto LoadResource = Core::RawVFunc<
        /* offset = */ 0x260,
        /* type = */ uint64_t(Red::IComponent::*)(Red::JobQueue& aJobQueue),
        /* verified = */ true>();

constexpr auto RefreshAppearance = Core::RawVFunc<
        /* offset = */ 0x280,
        /* type = */ void(Red::IComponent::*)(),
        /* verified = */ true>();
}
