public native class animAnimGraph extends CResource {
  public native let rootNode: ref<animAnimNode_Root>;
  public native let variables: ref<animAnimVariableContainer>;
  public native let animFeatures: array<animAnimFeatureEntry>;
  public native let timeDeltaMultiplier: Float;
  public native let isPaused: Bool;
  public native let oneFrameToggle: Bool;
  public native let hasMixerSlot: Bool;
  public native let additionalAnimDatabases: array<animAnimDatabaseCollectionEntry>;
  public native let nodesToInit: array<ref<animAnimNode_Base>>;
  public native let useLunaticMode: Bool;
  public native let useAnimCommands: Bool;
  public native let useAnimCommandsForCrowd: Bool;
  public native let useAnimStaticCommands: Bool;
  public native let staticCommandsRig: ResourceRef; // rRef<animRig>
  public native let hackAlwaysSample: Bool;
}
