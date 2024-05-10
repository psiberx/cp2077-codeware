public native struct gameActionRotateBaseState {
  native let replicationId: Uint32;
  native let type: Uint16;
  native let startTimeStamp: netTime;
  native let stopTimeStamp: netTime;
  native let updateBucket: Uint8;
  native let angleOffset: Float;
  native let angleTolerance: Float;
  native let keepUpdatingTarget: Bool;
  native let useRotationTime: Bool;
  native let rotationSpeed: Float;
  native let rotationTime: Float;
}
