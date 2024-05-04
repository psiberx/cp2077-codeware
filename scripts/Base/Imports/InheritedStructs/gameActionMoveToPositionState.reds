public native struct gameActionMoveToPositionState {
  native let replicationId: Uint32;
  native let type: Uint16;
  native let startTimeStamp: netTime;
  native let stopTimeStamp: netTime;
  native let updateBucket: Uint8;

  native let target: Vector3;
  native let useSpotReservation: Bool;
  native let usePathfinding: Bool;
  native let useStart: Bool;
  native let useStop: Bool;
  native let movementType: moveMovementType;
  native let strafingTarget: wref<GameObject>;
}
