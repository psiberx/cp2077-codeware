public native struct gameuiHUDVideoStartEvent {
  native let videoPathHash: Uint64;
  native let playOnHud: Bool;
  native let fullScreen: Bool;
  native let useFullscreenVideoState: Bool;
  native let keepWidescreenAspectRatio: Bool;
  native let position: Vector2;
  native let size: Vector2;
  native let skippable: Bool;
  native let isLooped: Bool;
  native let forceVideoFrameRate: Bool;
}
