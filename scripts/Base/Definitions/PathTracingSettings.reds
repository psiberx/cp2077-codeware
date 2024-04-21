public native class PathTracingSettings extends IAreaSettings {
  native let albedoModulation: Float;
  native let diffuseGlobalScale: Float;
  native let diffuseSunScale: Float;
  native let diffuseSkyScale: Float;
  native let diffuseLocalLightsScale: Float;
  native let diffuseEmissiveScale: Float;
  native let specularGlobalScale: Float;
  native let specularSunScale: Float;
  native let specularSkyScale: Float;
  native let specularLocalLightsScale: Float;
  native let specularEmissiveScale: Float;
  native let maxIntensity: Float;
  native let GIOnlyLightScale: Float;
  native let rayNumber: Uint32;
  native let bounceNumber: Uint32;
  native let rayNumberScreenshot: Uint32;
  native let bounceNumberScreenshot: Uint32;
}
