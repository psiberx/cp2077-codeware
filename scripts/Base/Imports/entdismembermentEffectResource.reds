public native class entdismembermentEffectResource extends ISerializable {
  public native let Name: CName;
  public native let AppearanceNames: array<CName>;
  public native let BodyPartMask: Uint32; // physicsRagdollBodyPartE
  public native let Offset: Transform;
  public native let Placement: Uint16; // entdismembermentPlacementE
  public native let ResourceSets: Uint16; // entdismembermentResourceSetMask
  public native let WoundType: Uint16; // entdismembermentWoundTypeE
  public native let Effect: ResourceAsyncRef; // raRef<worldEffect>
  public native let MatchToWoundByName: Bool;
}
