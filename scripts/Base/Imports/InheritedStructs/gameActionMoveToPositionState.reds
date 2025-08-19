public native struct gameActionMoveToPositionState {
  public native let replicationId: Uint32;
  public native let type: Uint16;
  public native let startTimeStamp: netTime;
  public native let stopTimeStamp: netTime;
  public native let updateBucket: Uint8;
  public native let target: Vector3;
  public native let useSpotReservation: Bool;
  public native let usePathfinding: Bool;
  public native let useStart: Bool;
  public native let useStop: Bool;
  public native let movementType: moveMovementType;
  public native let strafingTarget: wref<GameObject>;
}
