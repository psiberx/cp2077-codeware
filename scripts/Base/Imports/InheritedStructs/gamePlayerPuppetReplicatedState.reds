public native struct gamePlayerPuppetReplicatedState {
  public native let initialOrientation: EulerAngles;
  public native let initialLocation: Vector3;
  public native let initialAppearance: CName;
  public native let actionsBuffer: gameActionsReplicationBuffer;
  public native let health: Float;
  public native let armor: Float;
  public native let hasCPOMissionData: Bool;
  public native let CPOMissionVotedHistory: array<CName>;
  public native let animEventsState: gameReplicatedAnimControllerEventsState;
  public native let entityEventsState: gameReplicatedEntityEventsState;
  public native let recordID: TweakDBID;
  public native let persistentID: Uint64;
}
