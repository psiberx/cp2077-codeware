public native class animAnimationBufferCompressed extends animIAnimationBuffer {
  native let duration: Float;
  native let numFrames: Uint32;
  native let numExtraJoints: Uint8;
  native let numExtraTracks: Uint8;
  native let numJoints: Uint16;
  native let numTracks: Uint16;
  native let numAnimKeys: Uint32;
  native let numAnimKeysRaw: Uint32;
  native let numConstAnimKeys: Uint32;
  native let numTrackKeys: Uint32;
  native let numConstTrackKeys: Uint32;
  native let isScaleConstant: Bool;
  native let hasRawRotations: Bool;
  native let fallbackFrameIndices: array<Uint16>;
  native let dataAddress: animAnimDataAddress;
  native let extraDataNames: array<CName>;
}
