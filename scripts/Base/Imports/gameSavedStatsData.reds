public importonly struct gameSavedStatsData {
  public native let statModifiers: array<ref<gameStatModifierData>>;
  public native let inactiveStats: array<gamedataStatType>;
  public native let recordID: TweakDBID;
  public native let seed: Uint32;
}
