public native class entdismembermentWoundResource extends ISerializable {
  public native let Name: CName;
  public native let CullObject: entdismembermentCullObject;
  public native let GarmentMorphStrength: Float;
  public native let UseProceduralCut: Bool;
  public native let UseSingleMeshForRagdoll: Bool;
  public native let IsCritical: Bool;
  public native let Resources: array<entdismembermentWoundMeshes>;
  public native let Decals: array<entdismembermentWoundDecal>;
  public native let CensoredPaths: array<Uint64>;
  public native let CensoredCookedPaths: array<ResourceAsyncRef>;
  public native let CensorshipValid: Bool;
}
