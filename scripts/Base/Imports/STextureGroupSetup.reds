public native struct STextureGroupSetup {
  public native let group: GpuWrapApieTextureGroup;
  public native let rawFormat: ETextureRawFormat;
  public native let compression: ETextureCompression;
  public native let isStreamable: Bool;
  public native let hasMipchain: Bool;
  public native let isGamma: Bool;
  public native let platformMipBiasPC: Uint8;
  public native let platformMipBiasConsole: Uint8;
  public native let allowTextureDowngrade: Bool;
}
