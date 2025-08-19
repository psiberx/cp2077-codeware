public native class questCharacterEquippedItem_ConditionType extends questICharacterConditionType {
  public native let isPlayer: Bool;
  public native let puppetRef: EntityReference;
  public native let itemID: TweakDBID;
  public native let itemTag: CName;
  public native let excludedTweakDBIDs: array<TweakDBID>;
  public native let excludedTags: array<CName>;
  public native let inverted: Bool;
}
