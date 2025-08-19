public native struct gameActionDieState {
  public native let replicationId: Uint32;
  public native let type: Uint16;
  public native let startTimeStamp: netTime;
  public native let stopTimeStamp: netTime;
  public native let updateBucket: Uint8;
  public native let owner: wref<GameObject>;
  public native let movingAgent: wref<moveComponent>;
  public native let ragdollComponent: wref<RagdollComponent>;
  public native let slotComponent: wref<SlotComponent>;
}
