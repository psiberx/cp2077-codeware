public native struct STextureGroupSetup {
  native let group: GpuWrapApieTextureGroup;
  native let rawFormat: ETextureRawFormat;
  native let compression: ETextureCompression;
  native let isStreamable: Bool;
  native let hasMipchain: Bool;
  native let isGamma: Bool;
  native let platformMipBiasPC: Uint8;
  native let platformMipBiasConsole: Uint8;
  native let allowTextureDowngrade: Bool;
}
