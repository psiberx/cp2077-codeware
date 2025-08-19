public native class questPlayerLookAt_NodeType extends questISceneManagerNodeType {
  public native let useOffsetToPlayer: Bool;
  public native let objectRef: EntityReference;
  public native let slotName: CName;
  public native let offsetPos: Vector3;
  public native let duration: Float;
  public native let adjustPitch: Bool;
  public native let adjustYaw: Bool;
  public native let endOnTargetReached: Bool;
  public native let endOnCameraInputApplied: Bool;
  public native let endOnTimeExceeded: Bool;
  public native let cameraInputMagToBreak: Float;
  public native let precision: Float;
  public native let maxDuration: Float;
  public native let easeIn: Bool;
  public native let easeOut: Bool;
}
