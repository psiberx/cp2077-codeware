public native class questFollowParams extends AICommandParams {
  native let companionRef: ref<questUniversalRef>;
  native let companionDistance: Float;
  native let destinationPointTolerance: Float;
  native let stopWhenDestinationReached: Bool;
  native let movementType: moveMovementType;
  native let matchSpeed: Bool;
  native let useTeleport: Bool;
  native let repeatCommandOnInterrupt: Bool;
}
