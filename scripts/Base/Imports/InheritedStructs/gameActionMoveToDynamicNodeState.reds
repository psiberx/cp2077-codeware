public native struct gameActionMoveToDynamicNodeState {
  native let targetPos: Vector3;
  native let toleranceRadius: Float;
  native let rotateEntity: Bool;
  native let moveStyle: Uint32;

  native let replicationId: Uint32;
  native let type: Uint16;
  native let startTimeStamp: netTime;
  native let stopTimeStamp: netTime;
  native let updateBucket: Uint8;

  native let target: wref<GameObject>;
  native let strafingTarget: wref<GameObject>;
  native let desiredDistanceFromTarget: Float;
  native let stopWhenDestinationReached: Bool;
  native let pathfindingUpdateInterval: Float;
  native let usePathfinding: Bool;
  native let useStart: Bool;
  native let useStop: Bool;
}
