public native struct gameMovingPlatformSavedData {
  public native let currentLocalPosition: Vector4;
  public native let movement: ref<IMovingPlatformMovement>;
  public native let destinationName: CName;
  public native let destinationData: Int32;
  public native let time: Float;
  public native let maxTime: Float;
  public native let mountedPlayerEntityID: Uint32;
  public native let isPaused: Bool;
}
