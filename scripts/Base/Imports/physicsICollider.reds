public abstract native class physicsICollider extends ISerializable {
  public native let localToBody: Transform;
  public native let material: CName;
  public native let materialApperanceOverrides: array<physicsApperanceMaterial>;
  public native let tag: CName;
  public native let isImported: Bool;
  public native let isQueryShapeOnly: Bool;
  public native let volumeModifier: Float;
  public native let filterData: ref<physicsFilterData>;
}
