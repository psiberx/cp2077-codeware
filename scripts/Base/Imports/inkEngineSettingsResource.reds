public native class inkEngineSettingsResource extends CResource {
  public native let fallbackCompositionResource: ResourceRef; // rRef<inkFullscreenCompositionResource>
  public native let fallbackShapeCollectionResource: ResourceRef; // rRef<inkShapeCollectionResource>
  public native let fallbackIconAtlasResource: ResourceRef; // rRef<inkTextureAtlas>
  public native let inputKeyIconsDefinitionResource: ResourceAsyncRef; // raRef<JsonResource>
  public native let fallbackFontFamilyPath: ResourceRef; // rRef<inkFontFamilyResource>
  public native let blackTexture: ResourceRef; // rRef<CBitmapTexture>
  public native let advertMissingFormatTexture: ResourceRef; // rRef<CBitmapTexture>
  public native let advertWrongResourceTexture: ResourceRef; // rRef<CBitmapTexture>
  public native let fallbackTextureAtlas: ResourceRef; // rRef<inkTextureAtlas>
  public native let imageTilingMaterial: ResourceRef; // rRef<IMaterial>
  public native let imageNineSliceMaterial: ResourceRef; // rRef<IMaterial>
  public native let depthMaterial: ResourceRef; // rRef<IMaterial>
  public native let whiteMaskAtlas: ResourceRef; // rRef<inkTextureAtlas>
  public native let defaultBinkMaterial: ResourceRef; // rRef<CMaterialTemplate>
  public native let tooManyBinksTexture: ResourceRef; // rRef<CBitmapTexture>
  public native let componentMissingTexture: ResourceRef; // rRef<CBitmapTexture>
}
