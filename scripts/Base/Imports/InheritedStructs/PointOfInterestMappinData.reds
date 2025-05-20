public importonly struct PointOfInterestMappinData {
  native let typedVariant: ref<gamemappinsIPointOfInterestVariant>;
  native let active: Bool;
  native let slotName: CName;
  native let slotOffset: Vector3;
  native let dynamicMappinRadius: Float;
  native let staticMappinDef: TweakDBID;
  native let dynamicMappinDef: TweakDBID;
}
