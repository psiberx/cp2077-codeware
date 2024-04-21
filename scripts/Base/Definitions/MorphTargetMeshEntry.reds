public native struct MorphTargetMeshEntry {
  native let name: CName;
  native let regionName: CName;
  native let faceRegion: MorphTargetsFaceRegion;
  native let boneNames: array<CName>;
  native let boneRigMatrices: array<Matrix>;
}
