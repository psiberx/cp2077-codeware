public native class VolumetricFogAreaSettings extends IAreaSettings {
  native let albedo: CurveDataHDRColor;
  native let range: CurveDataFloat;
  native let fogHeight: CurveDataFloat;
  native let fogHeightFalloff: CurveDataFloat;
  native let fogHeightMaxCut: CurveDataFloat;
  native let density: CurveDataFloat;
  native let absorption: CurveDataFloat;
  native let ambientScale: CurveDataFloat;
  native let localAmbientScale: CurveDataFloat;
  native let globalLightScale: CurveDataFloat;
  native let globalLightAnisotropy: CurveDataFloat;
  native let globalLightAnisotropyBase: CurveDataFloat;
  native let globalLightAnisotropyScale: CurveDataFloat;
  native let localLightRange: CurveDataFloat;
  native let localLightScale: CurveDataFloat;
  native let distantAlbedo: CurveDataHDRColor;
  native let distantGlobalLightScale: CurveDataFloat;
  native let distantGroundIrradiance: CurveDataFloat;
  native let distantGroundSaturation: CurveDataFloat;
  native let distantSkyIrradiance: CurveDataFloat;
  native let distantShadowAmbientDarkening: CurveDataFloat;
}
