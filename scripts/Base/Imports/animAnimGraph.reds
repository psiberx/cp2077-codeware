public native class animAnimGraph extends CResource {
  native let animFeatures: array<animAnimFeatureEntry>;
  native let timeDeltaMultiplier: Float;
  native let isPaused: Bool;
  native let oneFrameToggle: Bool;
  native let hasMixerSlot: Bool;
  native let additionalAnimDatabases: array<animAnimDatabaseCollectionEntry>;
  native let useLunaticMode: Bool;
  native let useAnimCommands: Bool;
  native let useAnimCommandsForCrowd: Bool;
  native let useAnimStaticCommands: Bool;
  native let staticCommandsRig: ResourceRef; // rRef<animRig>
  native let hackAlwaysSample: Bool;
}
