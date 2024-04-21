public native class animSimpleBounce_JsonProperties extends ISerializable {
  native let multiplier: Float;
  native let negativeMultiplier: Float;
  native let smoothStep: Float;
  native let offset: Float;
  native let delay: Float;
  native let startTransform: animTransformIndex;
  native let endTransform: animTransformIndex;
  native let transformOutputs: array<animSimpleBounceTransformOutput>;
  native let trackOutputs: array<animSimpleBounceTrackOutput>;
  native let outputDriverTrack: animNamedTrackIndex;
}
