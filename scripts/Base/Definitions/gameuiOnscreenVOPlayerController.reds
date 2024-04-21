public native class gameuiOnscreenVOPlayerController extends inkGameController {
  native let subtitlesContainer: inkCompoundRef;
  native let subtitlesLibraryResource: ResourceAsyncRef; // raRef<inkWidgetLibraryResource>
  native let subtitlesRootName: CName;
  native let audioVOList: array<gameuiVOWithDelay>;
}
