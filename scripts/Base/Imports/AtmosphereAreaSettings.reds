public native class AtmosphereAreaSettings extends IAreaSettings {
  native let skydomeColor: CurveDataHDRColor;
  native let skylightColor: CurveDataHDRColor;
  native let groundReflectance: CurveDataHDRColor;
  native let sunMinZ: CurveDataFloat;
  native let horizonMinZ: CurveDataFloat;
  native let horizonFalloff: CurveDataFloat;
  native let turbidity: CurveDataFloat;
  native let lutTurbidity: CurveDataFloat;
  native let artisticDarkeningColor: CurveDataHDRColor;
  native let artisticDarkeningStartPoint: CurveDataFloat;
  native let artisticDarkeningEndPoint: CurveDataFloat;
  native let artisticDarkeningExponent: CurveDataFloat;
  native let sunColor: CurveDataHDRColor;
  native let sunFalloff: CurveDataFloat;
  native let rayTracedSunShadowRange: CurveDataFloat;
  native let moonColor: CurveDataHDRColor;
  native let moonFalloff: CurveDataFloat;
  native let moonGlowIntensity: CurveDataFloat;
  native let moonGlowFalloff: CurveDataFloat;
  native let moonTexture: ResourceRef; // rRef<CBitmapTexture>
  native let galaxyIntensity: CurveDataFloat;
  native let starMapIntensity: CurveDataFloat;
  native let starMapBrightScale: CurveDataFloat;
  native let starMapDimScale: CurveDataFloat;
  native let starMapConstelationsScale: CurveDataFloat;
  native let starCornerLuminanceFix: CurveDataFloat;
  native let starMapTexture: ResourceRef; // rRef<CCubeTexture>
  native let galaxyTexture: ResourceRef; // rRef<CBitmapTexture>
  native let probeColorOverrideHorizon: CurveDataHDRColor;
  native let probeAlphaOverrideHorizon: CurveDataFloat;
  native let probeColorOverrideZenith: CurveDataHDRColor;
  native let probeAlphaOverrideZenith: CurveDataFloat;
}
