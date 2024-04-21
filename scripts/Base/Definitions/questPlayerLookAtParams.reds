public native class questPlayerLookAtParams extends ISerializable {
  native let useOffsetToPlayer: Bool;
  native let lookAtTarget: EntityReference;
  native let slotName: CName;
  native let offset: Vector3;
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
