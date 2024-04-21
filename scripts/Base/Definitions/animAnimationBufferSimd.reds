public native class animAnimationBufferSimd extends animIAnimationBuffer {
  native let duration: Float;
  native let numFrames: Uint32;
  native let numExtraJoints: Uint8;
  native let numExtraTracks: Uint8;
  native let numJoints: Uint16;
  native let numTracks: Uint16;
  native let numTranslationsToCopy: Uint16;
  native let numTranslationsToEvalAlignedToSimd: Uint16;
  native let quantizationBits: Uint16;
  native let isScaleConstant: Bool;
  native let isTrackConstant: Bool;
  native let dataAddress: animAnimDataAddress;
  native let fallbackFrameIndices: array<Uint16>;
  native let extraDataNames: array<CName>;
}
