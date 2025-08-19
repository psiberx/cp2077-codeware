public native struct gameFreeCameraSettings {
  public native let movPrecision: Float;
  public native let rotPrecision: Float;
  public native let roll: Float;
  public native let fov: Float;
  public native let dofIntensity: Float;
  public native let dofNearBlur: Float;
  public native let dofNearFocus: Float;
  public native let dofFarBlur: Float;
  public native let dofFarFocus: Float;
  public native let iso: Int32;
  public native let shutter: Float;
  public native let aperture: Float;
  public native let lights: array<gameFreeCameraLightSettings>;
}
