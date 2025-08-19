public native class inkCompositionPreviewSettings extends ISerializable {
  public native let sourceState: CName;
  public native let targetState: CName;
  public native let previewResolution: inkETextureResolution;
  public native let gameFrameTexture: ResourceAsyncRef; // raRef<CBitmapTexture>
  public native let textureAtlas: ResourceAsyncRef; // raRef<inkTextureAtlas>
  public native let texturePart: CName;
}
