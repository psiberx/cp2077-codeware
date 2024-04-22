public native struct ColorGradingLutParams {
  native let LUT: ResourceRef; // rRef<CBitmapTexture>
  native let inputMapping: EColorMappingFunction;
  native let outputMapping: EColorMappingFunction;
}
