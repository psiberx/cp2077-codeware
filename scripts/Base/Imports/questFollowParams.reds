public native class questFollowParams extends AICommandParams {
  public native let companionRef: ref<questUniversalRef>;
  public native let companionDistance: Float;
  public native let destinationPointTolerance: Float;
  public native let stopWhenDestinationReached: Bool;
  public native let movementType: moveMovementType;
  public native let matchSpeed: Bool;
  public native let useTeleport: Bool;
  public native let repeatCommandOnInterrupt: Bool;
}
