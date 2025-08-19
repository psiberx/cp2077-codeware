public native class questSceneNodeDefinition extends questSignalStoppingNodeDefinition {
  public native let sceneFile: ResourceAsyncRef; // raRef<scnSceneResource>
  public native let sceneLocation: scnWorldMarker;
  public native let interruptionOperations: array<ref<scnIInterruptionOperation>>;
  public native let syncToMusic: Bool;
  public native let notAllowedToBeFrozen: Bool;
  public native let reapplyInterruptionOperationsAfterGameLoad: Bool;
}
