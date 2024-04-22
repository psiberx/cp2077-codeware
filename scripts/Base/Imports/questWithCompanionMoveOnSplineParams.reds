public native struct questWithCompanionMoveOnSplineParams {
  native let movementType: AIMovementTypeSpec;
  native let rotateEntityTowardsFacingTarget: Bool;
  native let snapToTerrain: Bool;
  native let companionDistancePreset: gamedataCompanionDistancePreset;
  native let companionPosition: questCompanionPositions;
  native let catchUpWithCompanion: Bool;
  native let teleportToCompanion: Bool;
  native let useMatchForSpeedForPlayer: Bool;
  native let ignoreNavigation: Bool;
  native let ignoreLineOfSightCheck: Bool;
  native let useOffMeshLinkReservation: Bool;
  native let minSearchAngle: Float;
  native let maxSearchAngle: Float;
  native let interruptCapability: scnInterruptCapability;
  native let maxCompanionDistanceOnSpline: Float;
}
