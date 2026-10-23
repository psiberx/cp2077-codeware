#pragma once

// Patch 2.5 rebased worldInstancedMeshNode on worldCookedNode, so these offsets no longer apply.
// RTTI_EXPAND_CLASS(Red::worldInstancedMeshNode, {
//     RTTI_PROPERTY(Red::DynArray<Red::Box>, 0x50, "boundingBoxes");
//     RTTI_PROPERTY(Red::DynArray<float>, 0x60, "streamingDistances");
//     RTTI_PROPERTY(Red::DynArray<uint32_t>, 0x70, "instanceBatches");
// });
