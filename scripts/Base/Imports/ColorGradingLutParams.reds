public native struct ColorGradingLutParams {
  public native let LUT: ResourceRef; // rRef<CBitmapTexture>
  public native let inputMapping: EColorMappingFunction;
  public native let outputMapping: EColorMappingFunction;
}
