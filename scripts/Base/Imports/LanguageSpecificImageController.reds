public native class LanguageSpecificImageController extends inkLogicController {
  native let languages: array<LanguageSpecificImagData>;
  native let fallbackTextureAtlas: ResourceAsyncRef; // raRef<inkTextureAtlas>
  native let fallbackPartName: CName;
}
