public native struct gameActionEquipItemState {
  public native let replicationId: Uint32;
  public native let type: Uint16;
  public native let startTimeStamp: netTime;
  public native let stopTimeStamp: netTime;
  public native let updateBucket: Uint8;
  public native let slotId: TweakDBID;
  public native let itemId: ItemID;
  public native let animFeatureNameRight: CName;
  public native let animFeatureNameLeft: CName;
  public native let duration: Float;
  public native let spawnDelay: Float;
}
