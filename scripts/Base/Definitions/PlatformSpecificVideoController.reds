public native class PlatformSpecificVideoController extends inkLogicController {
  native let isLooped: Bool;
  native let video: ResourceAsyncRef; // raRef<Bink>
  native let video_PS4: ResourceAsyncRef; // raRef<Bink>
  native let video_XB1: ResourceAsyncRef; // raRef<Bink>
}
