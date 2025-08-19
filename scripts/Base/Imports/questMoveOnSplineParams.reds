public native class questMoveOnSplineParams extends AICommandParams {
  public native let splineNodeRef: NodeRef;
  public native let useStart: Bool;
  public native let useStop: Bool;
  public native let reverse: Bool;
  public native let startFromClosestPoint: Bool;
  public native let splineRecalculation: Bool;
  public native let additionalParams: ref<questMoveOnSplineAdditionalParams>;
  public native let useAlertedState: Bool;
  public native let useCombatState: Bool;
  public native let executeWhileDespawned: Bool;
  public native let repeatCommandOnInterrupt: Bool;
  public native let noWaitToEndDistance: Float;
  public native let noWaitToEndCompanionDistance: Float;
  public native let removeAfterCombat: Bool;
  public native let ignoreInCombat: Bool;
  public native let alwaysUseStealth: Bool;
  public native let disableFootIK: Bool;
}
