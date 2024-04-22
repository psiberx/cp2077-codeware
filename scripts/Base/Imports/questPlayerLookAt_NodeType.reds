public native class questPlayerLookAt_NodeType extends questISceneManagerNodeType {
  native let useOffsetToPlayer: Bool;
  native let objectRef: EntityReference;
  native let slotName: CName;
  native let offsetPos: Vector3;
  native let duration: Float;
  native let adjustPitch: Bool;
  native let adjustYaw: Bool;
  native let endOnTargetReached: Bool;
  native let endOnCameraInputApplied: Bool;
  native let endOnTimeExceeded: Bool;
  native let cameraInputMagToBreak: Float;
  native let precision: Float;
  native let maxDuration: Float;
  native let easeIn: Bool;
  native let easeOut: Bool;
}
