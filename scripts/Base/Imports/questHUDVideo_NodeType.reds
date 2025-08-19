public native class questHUDVideo_NodeType extends questIUIManagerNodeType {
  public native let video: ResourceAsyncRef; // raRef<Bink>
  public native let skippable: Bool;
  public native let audioEvent: CName;
  public native let syncToAudio: Bool;
  public native let retriggerAudioOnLoop: Bool;
  public native let looped: Bool;
  public native let forceVideoFrameRate: Bool;
  public native let playOnHud: Bool;
  public native let fullScreen: Bool;
  public native let useFullscreenVideoState: Bool;
  public native let keepWidescreenAspectRatio: Bool;
  public native let position: Vector2;
  public native let size: Vector2;
}
