#pragma once

RTTI_EXPAND_CLASS(Red::worldInstancedMeshNode, {
    RTTI_PROPERTY(Red::DynArray<Red::Box>, 0x50, "boundingBoxes");
    RTTI_PROPERTY(Red::DynArray<float>, 0x60, "streamingDistances");
    RTTI_PROPERTY(Red::DynArray<uint32_t>, 0x70, "instanceBatches");
});
