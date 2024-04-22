public native class animAnimNode_SimpleBounce extends animAnimNode_OnePoseInput {
  native let areChannelsResaved: Bool;
  native let outputDriverTrack: animNamedTrackIndex;
  native let debug: Bool;
  native let startTransform: animTransformIndex;
  native let endTransform: animTransformIndex;
  native let multiplier: Float;
  native let negativeMultiplier: Float;
  native let smoothStep: Float;
  native let offset: Float;
  native let delay: Float;
  native let transformOutputs: array<animSimpleBounceTransformOutput>;
  native let trackOutputs: array<animSimpleBounceTrackOutput>;
}
