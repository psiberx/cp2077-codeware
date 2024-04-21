public native class scnSceneSharedState extends ISerializable {
  native let entrypoint: CName;
  native let syncNodesVisited: array<scnSyncNodeSignal>;
  native let instanceHash: Uint64;
  native let finishedOnServer: Bool;
  native let finishedOnClient: Bool;
}
