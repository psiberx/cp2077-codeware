#pragma once

#include "Red/JobHandle.hpp"
#include "Red/Mesh.hpp"
#include "Red/Rendering.hpp"

namespace App
{
struct MeshAppearanceEx : Red::meshMeshAppearance
{
    void SetMesh(const Red::Handle<Red::CMesh>& aMesh)
    {
        Raw::MeshAppearance::Owner::Set(this, aMesh);
    }

    void ResetMaterialCache()
    {
        auto& materialJob = Raw::MeshAppearance::MaterialJob::Ref(this);
        auto& materialLock = Raw::MeshAppearance::MaterialLock::Ref(this);
        auto& materialData = Raw::MeshAppearance::MaterialData::Ref(this);
        auto& materialMap = Raw::MeshAppearance::MaterialMap::Ref(this);

        Raw::JobHandle::Wait(materialJob);

        std::scoped_lock _(materialLock);

        if (materialData)
        {
            Raw::RenderDataPtr::Release(materialData);
            materialData = nullptr;
        }

        materialMap.Clear();
    }
};
}

RTTI_EXPAND_CLASS(Red::meshMeshAppearance, App::MeshAppearanceEx, {
    RTTI_METHOD(SetMesh);
    RTTI_METHOD(ResetMaterialCache);
});
