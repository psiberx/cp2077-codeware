public native class questOverrideLoadingScreen_NodeType extends questIUIManagerNodeType {
  native let video: ResourceAsyncRef; // raRef<Bink>
  native let videos: array<ResourceAsyncRef>;
  native let minimumPlayCount: Uint32;
  native let forceVideoFrameRate: Bool;
  native let tooltips: array<String>;
  native let tooltipDuration: Float;
  native let glitchEffectTime: Float;
  native let keepLoadingScreenWhileVideoIsPlaying: Bool;
}
