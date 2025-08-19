public native struct questSimpleMoveOnSplineParams {
  public native let movementType: moveMovementType;
  public native let facingTargetRef: ref<questUniversalRef>;
  public native let rotateEntityTowardsFacingTarget: Bool;
  public native let snapToTerrain: Bool;
  public native let useOffMeshLinkReservation: Bool;
  public native let allowCrowdOnPath: Bool;
}
