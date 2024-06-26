public native class questSceneNodeDefinition extends questSignalStoppingNodeDefinition {
  native let sceneFile: ResourceAsyncRef; // raRef<scnSceneResource>
  native let sceneLocation: scnWorldMarker;
  native let interruptionOperations: array<ref<scnIInterruptionOperation>>;
  native let syncToMusic: Bool;
  native let notAllowedToBeFrozen: Bool;
  native let reapplyInterruptionOperationsAfterGameLoad: Bool;
}
