public native struct gameMovingPlatformSavedData {
  native let currentLocalPosition: Vector4;
  native let movement: ref<IMovingPlatformMovement>;
  native let destinationName: CName;
  native let destinationData: Int32;
  native let time: Float;
  native let maxTime: Float;
  native let mountedPlayerEntityID: Uint32;
  native let isPaused: Bool;
}
