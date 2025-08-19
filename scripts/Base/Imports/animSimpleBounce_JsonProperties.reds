public native class animSimpleBounce_JsonProperties extends ISerializable {
  public native let multiplier: Float;
  public native let negativeMultiplier: Float;
  public native let smoothStep: Float;
  public native let offset: Float;
  public native let delay: Float;
  public native let startTransform: animTransformIndex;
  public native let endTransform: animTransformIndex;
  public native let transformOutputs: array<animSimpleBounceTransformOutput>;
  public native let trackOutputs: array<animSimpleBounceTrackOutput>;
  public native let outputDriverTrack: animNamedTrackIndex;
}
