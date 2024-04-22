public native class questCharacterEquippedItem_ConditionType extends questICharacterConditionType {
  native let isPlayer: Bool;
  native let puppetRef: EntityReference;
  native let itemID: TweakDBID;
  native let itemTag: CName;
  native let excludedTweakDBIDs: array<TweakDBID>;
  native let excludedTags: array<CName>;
  native let inverted: Bool;
}
