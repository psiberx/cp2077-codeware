public native struct questWithCompanionMoveOnSplineParams {
  native let movementType: AIMovementTypeSpec;
  native let facingTargetRef: ref<questUniversalRef>;
  native let rotateEntityTowardsFacingTarget: Bool;
  native let snapToTerrain: Bool;
  native let shootingTargetRef: ref<questUniversalRef>;
  native let companionRef: ref<questUniversalRef>;
  native let companionDistancePreset: gamedataCompanionDistancePreset;
  native let companionPosition: questCompanionPositions;
  native let catchUpWithCompanion: Bool;
  native let teleportToCompanion: Bool;
  native let useMatchForSpeedForPlayer: Bool;
  native let ignoreNavigation: Bool;
  native let ignoreLineOfSightCheck: Bool;
  native let useOffMeshLinkReservation: Bool;
  native let lookAtTargetRef: ref<questUniversalRef>;
  native let minSearchAngle: Float;
  native let maxSearchAngle: Float;
  native let interruptCapability: scnInterruptCapability;
  native let maxCompanionDistanceOnSpline: Float;
}
