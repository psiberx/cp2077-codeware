public native class inkCompositionPreviewSettings extends ISerializable {
  native let sourceState: CName;
  native let targetState: CName;
  native let previewResolution: inkETextureResolution;
  native let gameFrameTexture: ResourceAsyncRef; // raRef<CBitmapTexture>
  native let textureAtlas: ResourceAsyncRef; // raRef<inkTextureAtlas>
  native let texturePart: CName;
}
