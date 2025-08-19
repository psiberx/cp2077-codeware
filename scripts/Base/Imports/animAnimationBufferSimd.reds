public native class animAnimationBufferSimd extends animIAnimationBuffer {
  public native let duration: Float;
  public native let numFrames: Uint32;
  public native let numExtraJoints: Uint8;
  public native let numExtraTracks: Uint8;
  public native let numJoints: Uint16;
  public native let numTracks: Uint16;
  public native let numTranslationsToCopy: Uint16;
  public native let numTranslationsToEvalAlignedToSimd: Uint16;
  public native let quantizationBits: Uint16;
  public native let isScaleConstant: Bool;
  public native let isTrackConstant: Bool;
  public native let dataAddress: animAnimDataAddress;
  public native let fallbackFrameIndices: array<Uint16>;
  public native let extraDataNames: array<CName>;
}
