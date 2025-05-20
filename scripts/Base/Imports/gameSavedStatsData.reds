public importonly struct gameSavedStatsData {
  native let statModifiers: array<ref<gameStatModifierData>>;
  native let inactiveStats: array<gamedataStatType>;
  native let recordID: TweakDBID;
  native let seed: Uint32;
}
