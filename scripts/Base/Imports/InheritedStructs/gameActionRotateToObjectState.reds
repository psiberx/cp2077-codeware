public native struct gameActionRotateToObjectState {
  public native let angleOffset: Float;
  public native let angleTolerance: Float;
  public native let keepUpdatingTarget: Bool;
  public native let useRotationTime: Bool;
  public native let rotationSpeed: Float;
  public native let rotationTime: Float;
  public native let replicationId: Uint32;
  public native let type: Uint16;
  public native let startTimeStamp: netTime;
  public native let stopTimeStamp: netTime;
  public native let updateBucket: Uint8;
  public native let targetObject: wref<GameObject>;
  public native let completeWhenRotated: Bool;
}
