public native struct MorphTargetMeshEntry {
  public native let name: CName;
  public native let regionName: CName;
  public native let faceRegion: MorphTargetsFaceRegion;
  public native let boneNames: array<CName>;
  public native let boneRigMatrices: array<Matrix>;
}
