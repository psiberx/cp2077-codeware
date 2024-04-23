public native struct questSimpleMoveOnSplineParams {
  native let movementType: moveMovementType;
  native let facingTargetRef: ref<questUniversalRef>;
  native let rotateEntityTowardsFacingTarget: Bool;
  native let snapToTerrain: Bool;
  native let useOffMeshLinkReservation: Bool;
  native let allowCrowdOnPath: Bool;
}
