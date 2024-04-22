public native struct LanguageSpecificImagData {
  native let languageID: inkLanguageId;
  native let textureAtlasForLanguage: ResourceAsyncRef; // raRef<inkTextureAtlas>
  native let partNameForLanguage: CName;
}
