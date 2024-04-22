public native struct inkTextureSlot {
  native let texture: ResourceAsyncRef; // raRef<CBitmapTexture>
  native let parts: array<inkTextureAtlasMapper>;
  native let slices: array<inkTextureAtlasSlice>;
}
