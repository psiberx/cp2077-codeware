public native class AtmosphereAreaSettings extends IAreaSettings {
  public native let skydomeColor: CurveDataHDRColor;
  public native let skylightColor: CurveDataHDRColor;
  public native let groundReflectance: CurveDataHDRColor;
  public native let sunMinZ: CurveDataFloat;
  public native let horizonMinZ: CurveDataFloat;
  public native let horizonFalloff: CurveDataFloat;
  public native let turbidity: CurveDataFloat;
  public native let lutTurbidity: CurveDataFloat;
  public native let artisticDarkeningColor: CurveDataHDRColor;
  public native let artisticDarkeningStartPoint: CurveDataFloat;
  public native let artisticDarkeningEndPoint: CurveDataFloat;
  public native let artisticDarkeningExponent: CurveDataFloat;
  public native let sunColor: CurveDataHDRColor;
  public native let sunFalloff: CurveDataFloat;
  public native let rayTracedSunShadowRange: CurveDataFloat;
  public native let moonColor: CurveDataHDRColor;
  public native let moonFalloff: CurveDataFloat;
  public native let moonGlowIntensity: CurveDataFloat;
  public native let moonGlowFalloff: CurveDataFloat;
  public native let moonTexture: ResourceRef; // rRef<CBitmapTexture>
  public native let galaxyIntensity: CurveDataFloat;
  public native let starMapIntensity: CurveDataFloat;
  public native let starMapBrightScale: CurveDataFloat;
  public native let starMapDimScale: CurveDataFloat;
  public native let starMapConstelationsScale: CurveDataFloat;
  public native let starCornerLuminanceFix: CurveDataFloat;
  public native let starMapTexture: ResourceRef; // rRef<CCubeTexture>
  public native let galaxyTexture: ResourceRef; // rRef<CBitmapTexture>
  public native let probeColorOverrideHorizon: CurveDataHDRColor;
  public native let probeAlphaOverrideHorizon: CurveDataFloat;
  public native let probeColorOverrideZenith: CurveDataHDRColor;
  public native let probeAlphaOverrideZenith: CurveDataFloat;
}
