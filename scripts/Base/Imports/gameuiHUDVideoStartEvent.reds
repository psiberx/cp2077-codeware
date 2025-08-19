public native struct gameuiHUDVideoStartEvent {
  public native let videoPathHash: Uint64;
  public native let playOnHud: Bool;
  public native let fullScreen: Bool;
  public native let useFullscreenVideoState: Bool;
  public native let keepWidescreenAspectRatio: Bool;
  public native let position: Vector2;
  public native let size: Vector2;
  public native let skippable: Bool;
  public native let isLooped: Bool;
  public native let forceVideoFrameRate: Bool;
}
