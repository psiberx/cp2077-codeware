public native class animCAnimationBufferBitwiseCompressed extends animIAnimationBuffer {
  native let version: Uint32;
  native let bones: array<animSAnimationBufferBitwiseCompressedBoneTrack>;
  native let tracks: array<animSAnimationBufferBitwiseCompressedData>;
  native let data: array<Int8>;
  native let fallbackData: array<Int8>;
  native let orientationCompressionMethod: SAnimationBufferOrientationCompressionMethod;
  native let duration: Float;
  native let numFrames: Uint32;
  native let dt: Float;
  native let streamingOption: SAnimationBufferStreamingOption;
  native let nonStreamableBones: Uint32;
  native let extraDataNames: array<CName>;
  native let numExtraBones: Uint32;
}
