public native class inkTextureAtlas extends CResource {
  native let activeTexture: inkTextureType;
  native let textureResolution: inkETextureResolution;
  native let texture: ResourceAsyncRef; // raRef<CBitmapTexture>
  native let dynamicTexture: ResourceAsyncRef; // raRef<DynamicTexture>
  native let parts: array<inkTextureAtlasMapper>;
  native let slices: array<inkTextureAtlasSlice>;
  native let slots: [inkTextureSlot; 3];
  native let dynamicTextureSlot: inkDynamicTextureSlot;
  native let isSingleTextureMode: Bool;
}
