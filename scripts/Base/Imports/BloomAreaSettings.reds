public native class BloomAreaSettings extends IAreaSettings {
  native let blurSizeX: Float;
  native let blurSizeY: Float;
  native let luminanceThresholdMin: Float;
  native let luminanceThresholdMax: Float;
  native let sceneColorScale: Float;
  native let bloomColorScale: Float;
  native let numDownsamplePasses: Uint8;
  native let shaftsAreaSettings: ShaftsAreaSettings;
}
