#pragma once

#include "Red/JobHandle.hpp"
#include "Red/Mesh.hpp"
#include "Red/Rendering.hpp"

namespace App
{
struct MeshAppearanceEx : Red::meshMeshAppearance
{
    static void SetMesh(const Red::Handle<Red::meshMeshAppearance>& aSelf, const Red::Handle<Red::CMesh>& aMesh)
    {
        Raw::MeshAppearance::Owner::Set(aSelf, aMesh);
    }

    static void ResetMaterialCache(const Red::Handle<Red::meshMeshAppearance>& aSelf)
    {
        auto& materialJob = Raw::MeshAppearance::MaterialJob::Ref(aSelf);
        auto& materialLock = Raw::MeshAppearance::MaterialLock::Ref(aSelf);
        auto& materialPtr = Raw::MeshAppearance::MaterialData::Ref(aSelf);
        auto& materialMap = Raw::MeshAppearance::MaterialMap::Ref(aSelf);
        auto& materialCached = Raw::MeshAppearance::ForceCache::Ref(aSelf);

        Red::WaitForJob(materialJob, std::chrono::milliseconds(5000));

        std::scoped_lock _(materialLock);

        if (materialPtr.data)
        {
            Raw::RenderData::Release(materialPtr.data);
            materialPtr.data = nullptr;
        }

        materialMap.Clear();
        materialCached = false;
    }
};
}

RTTI_EXPAND_CLASS(Red::meshMeshAppearance, App::MeshAppearanceEx, {
    RTTI_METHOD(SetMesh);
    RTTI_METHOD(ResetMaterialCache);
});
