public native struct gameStatModifierGroup {
  native let statModifierArray: array<gameStatModifierHandle>;
  native let statModifiersLimit: Int32;
  native let statModifiersLimitModifier: TweakDBID;
  native let relatedModifierGroups: array<TweakDBID>;
  native let statModifierGroupRecordID: TweakDBID;
  native let stackCount: Uint16;
  native let drawBasedOnStatType: Bool;
  native let saveBasedOnStatType: Bool;
  native let optimiseCombinedModifiers: Bool;
}
