public native struct inkDynamicTextureSlot {
  native let texture: ResourceAsyncRef; // raRef<DynamicTexture>
  native let parts: array<inkTextureAtlasMapper>;
}
