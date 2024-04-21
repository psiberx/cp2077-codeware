public native class questUseWorkspotParamsV1 extends AICommandParams {
  native persistent let function: questUseWorkspotNodeFunctions;
  native persistent let workspotNode: NodeRef;
  native persistent let teleport: Bool;
  native persistent let finishAnimation: Bool;
  native persistent let forceEntryAnimName: CName;
  native persistent let jumpToEntry: Bool;
  native persistent let entryId: WorkEntryId;
  native persistent let entryTag: CName;
  native persistent let changeWorkspot: Bool;
  native persistent let enableIdleMode: Bool;
  native persistent let exitEntryId: WorkEntryId;
  native persistent let exitAnimName: CName;
  native persistent let instant: Bool;
  native persistent let isWorkspotInfinite: Bool;
  native persistent let isPlayer: Bool;
  native persistent let playerParams: questUseWorkspotPlayerParams;
  native persistent let repeatCommandOnInterrupt: Bool;
  native persistent let workExcludedGestures: array<WorkEntryId>;
  native persistent let movementType: moveMovementType;
  native persistent let continueInCombat: Bool;
  native persistent let maxAnimTimeLimit: Float;
  native persistent let meshDissolvingEnabled: Bool;
  native persistent let dangleResetSimulation: Bool;
}
