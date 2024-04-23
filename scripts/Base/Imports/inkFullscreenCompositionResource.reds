public native class inkFullscreenCompositionResource extends CResource {
  native let compositionPresets: array<inkCompositionPreset>;
  native let backgroundMenuTextureUHDRes: ResourceAsyncRef; // raRef<CBitmapTexture>
  native let backgroundMenuTextureFHDRes: ResourceAsyncRef; // raRef<CBitmapTexture>
  native let previewSettings: ref<inkCompositionPreviewSettings>;
}
