public native struct rendRenderTextureBlobHeader {
  public native let version: Uint32;
  public native let sizeInfo: rendRenderTextureBlobSizeInfo;
  public native let textureInfo: rendRenderTextureBlobTextureInfo;
  public native let mipMapInfo: array<rendRenderTextureBlobMipMapInfo>;
  public native let histogramData: array<rendHistogramBias>;
  public native let flags: Uint32;
}
