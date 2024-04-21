public native class inkEngineSettingsResource extends CResource {
  native let fallbackCompositionResource: ResourceRef; // rRef<inkFullscreenCompositionResource>
  native let fallbackShapeCollectionResource: ResourceRef; // rRef<inkShapeCollectionResource>
  native let fallbackIconAtlasResource: ResourceRef; // rRef<inkTextureAtlas>
  native let inputKeyIconsDefinitionResource: ResourceAsyncRef; // raRef<JsonResource>
  native let fallbackFontFamilyPath: ResourceRef; // rRef<inkFontFamilyResource>
  native let blackTexture: ResourceRef; // rRef<CBitmapTexture>
  native let advertMissingFormatTexture: ResourceRef; // rRef<CBitmapTexture>
  native let advertWrongResourceTexture: ResourceRef; // rRef<CBitmapTexture>
  native let fallbackTextureAtlas: ResourceRef; // rRef<inkTextureAtlas>
  native let imageTilingMaterial: ResourceRef; // rRef<IMaterial>
  native let imageNineSliceMaterial: ResourceRef; // rRef<IMaterial>
  native let depthMaterial: ResourceRef; // rRef<IMaterial>
  native let whiteMaskAtlas: ResourceRef; // rRef<inkTextureAtlas>
  native let defaultBinkMaterial: ResourceRef; // rRef<CMaterialTemplate>
  native let tooManyBinksTexture: ResourceRef; // rRef<CBitmapTexture>
  native let componentMissingTexture: ResourceRef; // rRef<CBitmapTexture>
}
