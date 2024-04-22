public native class questHUDVideo_NodeType extends questIUIManagerNodeType {
  native let video: ResourceAsyncRef; // raRef<Bink>
  native let skippable: Bool;
  native let audioEvent: CName;
  native let syncToAudio: Bool;
  native let retriggerAudioOnLoop: Bool;
  native let looped: Bool;
  native let forceVideoFrameRate: Bool;
  native let playOnHud: Bool;
  native let fullScreen: Bool;
  native let useFullscreenVideoState: Bool;
  native let keepWidescreenAspectRatio: Bool;
  native let position: Vector2;
  native let size: Vector2;
}
