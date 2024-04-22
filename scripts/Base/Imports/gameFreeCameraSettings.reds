public native struct gameFreeCameraSettings {
  native let movPrecision: Float;
  native let rotPrecision: Float;
  native let roll: Float;
  native let fov: Float;
  native let dofIntensity: Float;
  native let dofNearBlur: Float;
  native let dofNearFocus: Float;
  native let dofFarBlur: Float;
  native let dofFarFocus: Float;
  native let iso: Int32;
  native let shutter: Float;
  native let aperture: Float;
  native let lights: array<gameFreeCameraLightSettings>;
}
