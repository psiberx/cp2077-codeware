public native class BloomAreaSettings extends IAreaSettings {
  public native let blurSizeX: Float;
  public native let blurSizeY: Float;
  public native let mipColors: [Color; 5];
  public native let mipLuminanceClamp: [Float; 3];
  public native let luminanceThresholdMin: Float;
  public native let luminanceThresholdMax: Float;
  public native let sceneColorScale: Float;
  public native let bloomColorScale: Float;
  public native let numDownsamplePasses: Uint8;
  public native let shaftsAreaSettings: ShaftsAreaSettings;
}
