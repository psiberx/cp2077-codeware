public native struct gameMuppetReplicatedState {
  native let recordID: TweakDBID;
  native let persistentID: Uint64;

  native let state: gameMuppetState;
  native let initialOrientation: EulerAngles;
  native let initialLocation: Vector3;
  native let health: Float;
  native let armor: Float;
}
