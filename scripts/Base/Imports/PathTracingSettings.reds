public native class PathTracingSettings extends IAreaSettings {
  public native let albedoModulation: Float;
  public native let diffuseGlobalScale: Float;
  public native let diffuseSunScale: Float;
  public native let diffuseSkyScale: Float;
  public native let diffuseLocalLightsScale: Float;
  public native let diffuseEmissiveScale: Float;
  public native let specularGlobalScale: Float;
  public native let specularSunScale: Float;
  public native let specularSkyScale: Float;
  public native let specularLocalLightsScale: Float;
  public native let specularEmissiveScale: Float;
  public native let maxIntensity: Float;
  public native let GIOnlyLightScale: Float;
  public native let rayNumber: Uint32;
  public native let bounceNumber: Uint32;
  public native let rayNumberScreenshot: Uint32;
  public native let bounceNumberScreenshot: Uint32;
}
