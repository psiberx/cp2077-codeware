public native struct gameActionMoveToState {
  native let replicationId: Uint32;
  native let type: Uint16;
  native let startTimeStamp: netTime;
  native let stopTimeStamp: netTime;
  native let updateBucket: Uint8;

  native let targetPos: Vector3;
  native let toleranceRadius: Float;
  native let rotateEntity: Bool;
  native let moveStyle: Uint32;
}
