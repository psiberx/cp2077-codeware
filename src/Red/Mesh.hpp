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
using MaterialData = Core::OffsetPtr<0x48, Red::RenderDataPtr>;
using Owner = Core::OffsetPtr<0x50, Red::CMesh*>;
using MaterialMap = Core::OffsetPtr<0x68, Red::Map<Red::CName, Red::Handle<Red::IMaterial>>>;
using MaterialJob = Core::OffsetPtr<0x90, Red::JobHandle>;
using MaterialLock = Core::OffsetPtr<0x98, Red::SharedSpinLock>;
using ForceCache = Core::OffsetPtr<0xA0, bool>;

constexpr auto LoadMaterialSetupAsync = Core::RawFunc<
    /* addr = */ Red::AddressLib::MeshAppearance_LoadMaterialSetupAsync,
    /* type = */ void (*)(Red::mesh::MeshAppearance& aAppearance, Red::Handle<Red::mesh::MeshAppearance>& aOut,
                          uint8_t a3)>();
}

namespace Raw::MeshComponent
{
constexpr auto LoadResource = Core::RawVFunc<
        /* offset = */ 0x260,
        /* type = */ uint64_t(Red::IComponent::*)(Red::JobQueue& aJobQueue)>();

constexpr auto RefreshAppearance = Core::RawVFunc<
        /* offset = */ 0x280,
        /* type = */ void(Red::IComponent::*)()>();
}
