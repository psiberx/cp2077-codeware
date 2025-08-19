public native class questMoveToParams extends AICommandParams {
  public native let movementTargetRef: ref<questUniversalRef>;
  public native let facingTargetRef: ref<questUniversalRef>;
  public native let rotateEntityTowardsFacingTarget: Bool;
  public native let movementType: moveMovementType;
  public native let ignoreNavigation: Bool;
  public native let useStart: Bool;
  public native let useStop: Bool;
  public native let desiredDistanceFromTarget: Float;
  public native let finishWhenDestinationReached: Bool;
  public native let repeatCommandOnInterrupt: Bool;
  public native let executeWhileDespawned: Bool;
  public native let removeAfterCombat: Bool;
  public native let ignoreInCombat: Bool;
  public native let alwaysUseStealth: Bool;
}
