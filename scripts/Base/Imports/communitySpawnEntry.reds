public native class communitySpawnEntry extends ISerializable {
  public native let entryName: CName;
  public native let characterRecordId: TweakDBID;
  public native let phases: array<ref<communitySpawnPhase>>;
  public native let spawnInView: gameSpawnInViewState;
  public native let initializers: array<ref<communitySpawnInitializer>>;
}
