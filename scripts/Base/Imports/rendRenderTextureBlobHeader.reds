public native struct rendRenderTextureBlobHeader {
  native let version: Uint32;
  native let sizeInfo: rendRenderTextureBlobSizeInfo;
  native let textureInfo: rendRenderTextureBlobTextureInfo;
  native let mipMapInfo: array<rendRenderTextureBlobMipMapInfo>;
  native let histogramData: array<rendHistogramBias>;
  native let flags: Uint32;
}
