public native struct gameScanningComponentReplicatedState {
  public native let componentName: CName;
  public native let enabled: Bool;
  public native let scanningState: gameScanningState;
  public native let pctScanned: Float;
  public native let controllingPeerIDs: [netPeerID; 8];
}
