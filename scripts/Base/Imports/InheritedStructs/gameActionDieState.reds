public native struct gameActionDieState {
  native let replicationId: Uint32;
  native let type: Uint16;
  native let startTimeStamp: netTime;
  native let stopTimeStamp: netTime;
  native let updateBucket: Uint8;

  native let owner: wref<GameObject>;
  native let movingAgent: wref<moveComponent>;
  native let ragdollComponent: wref<RagdollComponent>;
  native let slotComponent: wref<SlotComponent>;
}
