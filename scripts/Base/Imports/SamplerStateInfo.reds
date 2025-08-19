public native struct SamplerStateInfo {
  public native let filteringMin: ETextureFilteringMin;
  public native let filteringMag: ETextureFilteringMag;
  public native let filteringMip: ETextureFilteringMip;
  public native let addressU: ETextureAddressing;
  public native let addressV: ETextureAddressing;
  public native let addressW: ETextureAddressing;
  public native let comparisonFunc: ETextureComparisonFunction;
  public native let register: Uint8;
}
