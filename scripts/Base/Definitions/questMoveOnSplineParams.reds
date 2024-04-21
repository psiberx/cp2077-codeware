public native class questMoveOnSplineParams extends AICommandParams {
  native let splineNodeRef: NodeRef;
  native let useStart: Bool;
  native let useStop: Bool;
  native let reverse: Bool;
  native let startFromClosestPoint: Bool;
  native let splineRecalculation: Bool;
  native let useAlertedState: Bool;
  native let useCombatState: Bool;
  native let executeWhileDespawned: Bool;
  native let repeatCommandOnInterrupt: Bool;
  native let noWaitToEndDistance: Float;
  native let noWaitToEndCompanionDistance: Float;
  native let removeAfterCombat: Bool;
  native let ignoreInCombat: Bool;
  native let alwaysUseStealth: Bool;
  native let disableFootIK: Bool;
}
