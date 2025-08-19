public native struct gameStatModifierGroup {
  public native let statModifierArray: array<gameStatModifierHandle>;
  public native let statModifiersLimit: Int32;
  public native let statModifiersLimitModifier: TweakDBID;
  public native let relatedModifierGroups: array<TweakDBID>;
  public native let statModifierGroupRecordID: TweakDBID;
  public native let stackCount: Uint16;
  public native let drawBasedOnStatType: Bool;
  public native let saveBasedOnStatType: Bool;
  public native let optimiseCombinedModifiers: Bool;
}
