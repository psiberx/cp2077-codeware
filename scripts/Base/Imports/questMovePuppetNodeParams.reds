public native class questMovePuppetNodeParams extends AICommandParams {
  public native let moveType: questMoveType;
  public native let moveOnSplineParams: ref<questMoveOnSplineParams>;
  public native let moveToParams: ref<questMoveToParams>;
  public native let otherParams: ref<AICommandParams>;
  public native let repeatCommandOnInterrupt: Bool;
}
