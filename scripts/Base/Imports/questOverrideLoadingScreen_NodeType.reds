public native class questOverrideLoadingScreen_NodeType extends questIUIManagerNodeType {
  public native let video: ResourceAsyncRef; // raRef<Bink>
  public native let videos: array<ResourceAsyncRef>;
  public native let minimumPlayCount: Uint32;
  public native let forceVideoFrameRate: Bool;
  public native let tooltips: array<String>;
  public native let tooltipDuration: Float;
  public native let glitchEffectTime: Float;
  public native let keepLoadingScreenWhileVideoIsPlaying: Bool;
}
