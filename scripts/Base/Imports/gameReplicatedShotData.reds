public native struct gameReplicatedShotData {
  native let timeStamp: netTime;
  native let attackId: TweakDBID;
  native let target: wref<GameObject>;
  native let targetLocalOffset: Vector3;
}
