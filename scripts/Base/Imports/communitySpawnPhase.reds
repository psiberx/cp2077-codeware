public native class communitySpawnPhase extends ISerializable {
  native let phaseName: CName;
  native let appearances: array<CName>;
  native let timePeriods: array<communityPhaseTimePeriod>;
  native let alwaysSpawned: gameAlwaysSpawnedState;
  native let prefetchAppearance: Bool;
}
