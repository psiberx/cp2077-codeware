public native struct gameActionReplicatedState {
  public native let replicationId: Uint32;
  public native let type: Uint16;
  public native let startTimeStamp: netTime;
  public native let stopTimeStamp: netTime;
  public native let updateBucket: Uint8;
}
