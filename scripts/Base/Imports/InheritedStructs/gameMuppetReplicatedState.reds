public native struct gameMuppetReplicatedState {
  public native let recordID: TweakDBID;
  public native let persistentID: Uint64;
  public native let state: gameMuppetState;
  public native let initialOrientation: EulerAngles;
  public native let initialLocation: Vector3;
  public native let health: Float;
  public native let armor: Float;
}
