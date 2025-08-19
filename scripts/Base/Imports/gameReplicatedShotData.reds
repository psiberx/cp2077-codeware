public native struct gameReplicatedShotData {
  public native let timeStamp: netTime;
  public native let attackId: TweakDBID;
  public native let target: wref<GameObject>;
  public native let targetLocalOffset: Vector3;
}
