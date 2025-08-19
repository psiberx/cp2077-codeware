public native class animAnimationBufferCompressed extends animIAnimationBuffer {
  public native let duration: Float;
  public native let numFrames: Uint32;
  public native let numExtraJoints: Uint8;
  public native let numExtraTracks: Uint8;
  public native let numJoints: Uint16;
  public native let numTracks: Uint16;
  public native let numAnimKeys: Uint32;
  public native let numAnimKeysRaw: Uint32;
  public native let numConstAnimKeys: Uint32;
  public native let numTrackKeys: Uint32;
  public native let numConstTrackKeys: Uint32;
  public native let isScaleConstant: Bool;
  public native let hasRawRotations: Bool;
  public native let fallbackFrameIndices: array<Uint16>;
  public native let dataAddress: animAnimDataAddress;
  public native let extraDataNames: array<CName>;
}
