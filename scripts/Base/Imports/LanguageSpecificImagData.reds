public native struct LanguageSpecificImagData {
  public native let languageID: inkLanguageId;
  public native let textureAtlasForLanguage: ResourceAsyncRef; // raRef<inkTextureAtlas>
  public native let partNameForLanguage: CName;
}
