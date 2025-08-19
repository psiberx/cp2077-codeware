public native class animCAnimationBufferBitwiseCompressed extends animIAnimationBuffer {
  public native let version: Uint32;
  public native let bones: array<animSAnimationBufferBitwiseCompressedBoneTrack>;
  public native let tracks: array<animSAnimationBufferBitwiseCompressedData>;
  public native let data: array<Int8>;
  public native let fallbackData: array<Int8>;
  public native let orientationCompressionMethod: SAnimationBufferOrientationCompressionMethod;
  public native let duration: Float;
  public native let numFrames: Uint32;
  public native let dt: Float;
  public native let streamingOption: SAnimationBufferStreamingOption;
  public native let nonStreamableBones: Uint32;
  public native let extraDataNames: array<CName>;
  public native let numExtraBones: Uint32;
}
