public native class questMovePuppetNodeParams extends AICommandParams {
  native let moveType: questMoveType;
  native let moveOnSplineParams: ref<questMoveOnSplineParams>;
  native let moveToParams: ref<questMoveToParams>;
  native let otherParams: ref<AICommandParams>;
  native let repeatCommandOnInterrupt: Bool;
}
