public native struct gameDeviceBaseReplicationProxy {
  public native let recordID: TweakDBID;
  public native let persistentID: Uint64;
  public native let scriptState: ref<DeviceReplicatedState>;
  public native let versionId: Uint32;
  public native let versionTimestamp: netTime;
  public native let initialOrientation: EulerAngles;
  public native let initialLocation: Vector3;
}
