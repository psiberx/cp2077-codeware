public native class LanguageSpecificVideoController extends inkLogicController {
  public native let isLooped: Bool;
  public native let specificVideoForLanguage: ResourceAsyncRef; // raRef<Bink>
  public native let languages: array<inkLanguageId>;
  public native let fallbackVideo: ResourceAsyncRef; // raRef<Bink>
}
