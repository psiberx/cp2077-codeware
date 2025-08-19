public native class LanguageSpecificImageController extends inkLogicController {
  public native let languages: array<LanguageSpecificImagData>;
  public native let fallbackTextureAtlas: ResourceAsyncRef; // raRef<inkTextureAtlas>
  public native let fallbackPartName: CName;
}
