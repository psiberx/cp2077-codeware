public native class questCharacterManagerParameters_SetStatusEffect extends questICharacterManagerParameters_NodeSubType {
  public native let puppetRef: EntityReference;
  public native let isPlayer: Bool;
  public native let statusEffectID: TweakDBID;
  public native let isPlayerStatusEffectSource: Bool;
  public native let statusEffectSourceObject: EntityReference;
  public native let recordSelector: ref<questRecordSelector>;
  public native let set: Bool;
}
