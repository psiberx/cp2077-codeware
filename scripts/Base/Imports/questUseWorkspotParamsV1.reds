public native class questUseWorkspotParamsV1 extends AICommandParams {
  public native persistent let function: questUseWorkspotNodeFunctions;
  public native persistent let workspotNode: NodeRef;
  public native persistent let teleport: Bool;
  public native persistent let finishAnimation: Bool;
  public native persistent let forceEntryAnimName: CName;
  public native persistent let jumpToEntry: Bool;
  public native persistent let entryId: WorkEntryId;
  public native persistent let entryTag: CName;
  public native persistent let changeWorkspot: Bool;
  public native persistent let enableIdleMode: Bool;
  public native persistent let exitEntryId: WorkEntryId;
  public native persistent let exitAnimName: CName;
  public native persistent let instant: Bool;
  public native persistent let isWorkspotInfinite: Bool;
  public native persistent let isPlayer: Bool;
  public native persistent let playerParams: questUseWorkspotPlayerParams;
  public native persistent let repeatCommandOnInterrupt: Bool;
  public native persistent let workExcludedGestures: array<WorkEntryId>;
  public native persistent let movementType: moveMovementType;
  public native persistent let continueInCombat: Bool;
  public native persistent let maxAnimTimeLimit: Float;
  public native persistent let meshDissolvingEnabled: Bool;
  public native persistent let dangleResetSimulation: Bool;
}
