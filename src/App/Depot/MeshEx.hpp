#pragma once

RTTI_EXPAND_CLASS(Red::CMaterialInstance, {
    RTTI_PROPERTY(params);
});

RTTI_EXPAND_CLASS(Red::CMeshMaterialEntry, {
    RTTI_PROPERTY(materialWeak, "material");
});

RTTI_EXPAND_CLASS(Red::entMeshComponent, {
    RTTI_PROPERTY(Red::Handle<Red::CMesh>, 0x158, "meshResource");
});
