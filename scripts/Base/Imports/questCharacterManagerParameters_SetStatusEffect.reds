public native class questCharacterManagerParameters_SetStatusEffect extends questICharacterManagerParameters_NodeSubType {
  native let puppetRef: EntityReference;
  native let isPlayer: Bool;
  native let statusEffectID: TweakDBID;
  native let isPlayerStatusEffectSource: Bool;
  native let statusEffectSourceObject: EntityReference;
  native let recordSelector: ref<questRecordSelector>;
  native let set: Bool;
}
