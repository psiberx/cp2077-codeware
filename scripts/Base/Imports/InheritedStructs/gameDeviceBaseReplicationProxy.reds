public native struct gameDeviceBaseReplicationProxy {
  native let recordID: TweakDBID;
  native let persistentID: Uint64;

  native let scriptState: ref<DeviceReplicatedState>;
  native let versionId: Uint32;
  native let versionTimestamp: netTime;
  native let initialOrientation: EulerAngles;
  native let initialLocation: Vector3;
}
