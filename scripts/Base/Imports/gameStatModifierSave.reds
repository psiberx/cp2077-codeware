public importonly struct gameStatModifierSave {
  native let statModifierUnions: array<ref<gameStatModifierData>>;
  native let statsObjectID: StatsObjectID;
  native let recordID: TweakDBID;
  native let seed: Uint32;
}
