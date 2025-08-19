public native class VolumetricFogAreaSettings extends IAreaSettings {
  public native let albedo: CurveDataHDRColor;
  public native let range: CurveDataFloat;
  public native let fogHeight: CurveDataFloat;
  public native let fogHeightFalloff: CurveDataFloat;
  public native let fogHeightMaxCut: CurveDataFloat;
  public native let density: CurveDataFloat;
  public native let absorption: CurveDataFloat;
  public native let ambientScale: CurveDataFloat;
  public native let localAmbientScale: CurveDataFloat;
  public native let globalLightScale: CurveDataFloat;
  public native let globalLightAnisotropy: CurveDataFloat;
  public native let globalLightAnisotropyBase: CurveDataFloat;
  public native let globalLightAnisotropyScale: CurveDataFloat;
  public native let localLightRange: CurveDataFloat;
  public native let localLightScale: CurveDataFloat;
  public native let distantAlbedo: CurveDataHDRColor;
  public native let distantGlobalLightScale: CurveDataFloat;
  public native let distantGroundIrradiance: CurveDataFloat;
  public native let distantGroundSaturation: CurveDataFloat;
  public native let distantSkyIrradiance: CurveDataFloat;
  public native let distantShadowAmbientDarkening: CurveDataFloat;
}
