public native class entdismembermentWoundResource extends ISerializable {
  native let Name: CName;
  native let CullObject: entdismembermentCullObject;
  native let GarmentMorphStrength: Float;
  native let UseProceduralCut: Bool;
  native let UseSingleMeshForRagdoll: Bool;
  native let IsCritical: Bool;
  native let Resources: array<entdismembermentWoundMeshes>;
  native let Decals: array<entdismembermentWoundDecal>;
  native let CensoredPaths: array<Uint64>;
  native let CensoredCookedPaths: array<ResourceAsyncRef>;
  native let CensorshipValid: Bool;
}
