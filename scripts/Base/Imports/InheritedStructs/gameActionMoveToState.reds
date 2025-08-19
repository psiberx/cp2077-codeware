public native struct gameActionMoveToState {
  public native let replicationId: Uint32;
  public native let type: Uint16;
  public native let startTimeStamp: netTime;
  public native let stopTimeStamp: netTime;
  public native let updateBucket: Uint8;
  public native let targetPos: Vector3;
  public native let toleranceRadius: Float;
  public native let rotateEntity: Bool;
  public native let moveStyle: Uint32;
}
