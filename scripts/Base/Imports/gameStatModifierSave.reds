public importonly struct gameStatModifierSave {
  public native let statModifierUnions: array<ref<gameStatModifierData>>;
  public native let statsObjectID: StatsObjectID;
  public native let recordID: TweakDBID;
  public native let seed: Uint32;
}
