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
    }
};
}

RTTI_EXPAND_CLASS(Red::meshMeshAppearance, App::MeshAppearanceEx, {
    RTTI_METHOD(SetMesh);
    RTTI_METHOD(ResetMaterialCache);
});
