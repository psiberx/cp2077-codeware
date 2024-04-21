public native class questMoveToParams extends AICommandParams {
  native let rotateEntityTowardsFacingTarget: Bool;
  native let movementType: moveMovementType;
  native let ignoreNavigation: Bool;
  native let useStart: Bool;
  native let useStop: Bool;
  native let desiredDistanceFromTarget: Float;
  native let finishWhenDestinationReached: Bool;
  native let repeatCommandOnInterrupt: Bool;
  native let executeWhileDespawned: Bool;
  native let removeAfterCombat: Bool;
  native let ignoreInCombat: Bool;
  native let alwaysUseStealth: Bool;
}
