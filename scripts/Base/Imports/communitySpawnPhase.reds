public native class communitySpawnPhase extends ISerializable {
  public native let phaseName: CName;
  public native let appearances: array<CName>;
  public native let timePeriods: array<communityPhaseTimePeriod>;
  public native let alwaysSpawned: gameAlwaysSpawnedState;
  public native let prefetchAppearance: Bool;
}
