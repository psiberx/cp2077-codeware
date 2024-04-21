public native class animAnimNode_SimpleSpline extends animAnimNode_OnePoseInput {
  native let areSourceChannelsResaved: Bool;
  native let startTransform: animTransformIndex;
  native let middleTransform: animTransformIndex;
  native let endTransform: animTransformIndex;
  native let constrainedTransform: animTransformIndex;
  native let progressMode: animConstraintWeightMode;
  native let defaultProgress: Float;
  native let progressTrack: animNamedTrackIndex;
}
