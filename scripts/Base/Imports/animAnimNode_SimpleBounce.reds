public native class animAnimNode_SimpleBounce extends animAnimNode_OnePoseInput {
  public native let areChannelsResaved: Bool;
  public native let outputDriverTrack: animNamedTrackIndex;
  public native let debug: Bool;
  public native let startTransform: animTransformIndex;
  public native let endTransform: animTransformIndex;
  public native let multiplier: Float;
  public native let negativeMultiplier: Float;
  public native let smoothStep: Float;
  public native let offset: Float;
  public native let delay: Float;
  public native let transformOutputs: array<animSimpleBounceTransformOutput>;
  public native let trackOutputs: array<animSimpleBounceTrackOutput>;
}
