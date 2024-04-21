public native class DynamicTexture extends ITexture {
  native let width: Uint32;
  native let height: Uint32;
  native let scaleToViewport: Bool;
  native let mipChain: Bool;
  native let samplesCount: Uint8;
  native let dataFormat: DynamicTextureDataFormat;
}
