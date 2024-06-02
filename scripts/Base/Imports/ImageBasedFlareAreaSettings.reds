public native class ImageBasedFlareAreaSettings extends IAreaSettings {
  native let treshold: Float;
  native let dispersal: Float;
  native let haloWidth: Float;
  native let distortion: Float;
  native let curve: Float;
  native let tint: [Color; 8];
  native let scale: CurveDataFloat;
  native let saturation: CurveDataFloat;
}
