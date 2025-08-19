public importonly struct PointOfInterestMappinData {
  public native let typedVariant: ref<gamemappinsIPointOfInterestVariant>;
  public native let active: Bool;
  public native let slotName: CName;
  public native let slotOffset: Vector3;
  public native let dynamicMappinRadius: Float;
  public native let staticMappinDef: TweakDBID;
  public native let dynamicMappinDef: TweakDBID;
}
