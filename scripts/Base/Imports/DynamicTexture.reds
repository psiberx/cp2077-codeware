public native class DynamicTexture extends ITexture {
  public native let width: Uint32;
  public native let height: Uint32;
  public native let scaleToViewport: Bool;
  public native let mipChain: Bool;
  public native let samplesCount: Uint8;
  public native let dataFormat: DynamicTextureDataFormat;
  public native let generator: ref<IDynamicTextureGenerator>;
}
