public native class inkTextureAtlas extends CResource {
  public native let activeTexture: inkTextureType;
  public native let textureResolution: inkETextureResolution;
  public native let texture: ResourceAsyncRef; // raRef<CBitmapTexture>
  public native let dynamicTexture: ResourceAsyncRef; // raRef<DynamicTexture>
  public native let parts: array<inkTextureAtlasMapper>;
  public native let slices: array<inkTextureAtlasSlice>;
  public native let slots: [inkTextureSlot; 3];
  public native let dynamicTextureSlot: inkDynamicTextureSlot;
  public native let isSingleTextureMode: Bool;
}
