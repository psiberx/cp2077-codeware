public abstract native class physicsICollider extends ISerializable {
  native let localToBody: Transform;
  native let material: CName;
  native let materialApperanceOverrides: array<physicsApperanceMaterial>;
  native let tag: CName;
  native let isImported: Bool;
  native let isQueryShapeOnly: Bool;
  native let volumeModifier: Float;
  native let filterData: ref<physicsFilterData>;
}
