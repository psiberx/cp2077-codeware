public native class LanguageSpecificVideoController extends inkLogicController {
  native let isLooped: Bool;
  native let specificVideoForLanguage: ResourceAsyncRef; // raRef<Bink>
  native let languages: array<inkLanguageId>;
  native let fallbackVideo: ResourceAsyncRef; // raRef<Bink>
}
