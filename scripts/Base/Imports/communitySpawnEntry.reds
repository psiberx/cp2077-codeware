public native class communitySpawnEntry extends ISerializable {
  native let entryName: CName;
  native let characterRecordId: TweakDBID;
  native let phases: array<ref<communitySpawnPhase>>;
  native let spawnInView: gameSpawnInViewState;
  native let initializers: array<ref<communitySpawnInitializer>>;
}
