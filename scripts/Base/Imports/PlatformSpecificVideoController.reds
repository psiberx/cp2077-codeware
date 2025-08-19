public native class PlatformSpecificVideoController extends inkLogicController {
  public native let isLooped: Bool;
  public native let video: ResourceAsyncRef; // raRef<Bink>
  public native let video_PS4: ResourceAsyncRef; // raRef<Bink>
  public native let video_XB1: ResourceAsyncRef; // raRef<Bink>
}
