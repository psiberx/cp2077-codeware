public native class inkFullscreenCompositionResource extends CResource {
  public native let compositionPresets: array<inkCompositionPreset>;
  public native let backgroundMenuTextureUHDRes: ResourceAsyncRef; // raRef<CBitmapTexture>
  public native let backgroundMenuTextureFHDRes: ResourceAsyncRef; // raRef<CBitmapTexture>
  public native let previewSettings: ref<inkCompositionPreviewSettings>;
}
