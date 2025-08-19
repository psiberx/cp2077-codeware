public native class scnSceneSharedState extends ISerializable {
  public native let entrypoint: CName;
  public native let syncNodesVisited: array<scnSyncNodeSignal>;
  public native let instanceHash: Uint64;
  public native let finishedOnServer: Bool;
  public native let finishedOnClient: Bool;
}
