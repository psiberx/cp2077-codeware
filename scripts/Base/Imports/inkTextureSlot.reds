public native struct inkTextureSlot {
  public native let texture: ResourceAsyncRef; // raRef<CBitmapTexture>
  public native let parts: array<inkTextureAtlasMapper>;
  public native let slices: array<inkTextureAtlasSlice>;
}
