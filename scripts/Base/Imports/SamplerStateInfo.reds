public native struct SamplerStateInfo {
  native let filteringMin: ETextureFilteringMin;
  native let filteringMag: ETextureFilteringMag;
  native let filteringMip: ETextureFilteringMip;
  native let addressU: ETextureAddressing;
  native let addressV: ETextureAddressing;
  native let addressW: ETextureAddressing;
  native let comparisonFunc: ETextureComparisonFunction;
}
