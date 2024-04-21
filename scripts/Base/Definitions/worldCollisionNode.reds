public native class worldCollisionNode extends worldNode {
  native let numActors: Uint16;
  native let numShapeInfos: Uint16;
  native let numShapePositions: Uint16;
  native let numShapeRotations: Uint16;
  native let numScales: Uint16;
  native let numMaterials: Uint16;
  native let numPresets: Uint16;
  native let numMaterialIndices: Uint16;
  native let numShapeIndices: Uint16;
  native let sectorHash: Uint64;
  native let extents: Vector4;
  native let lod: Uint8;
  native let resourceVersion: Uint8;
}
