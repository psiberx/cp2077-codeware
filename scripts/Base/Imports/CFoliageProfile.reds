public native class CFoliageProfile extends CResource {
  public native let cutoffAlphaMinMip: Float;
  public native let cutoffAlphaMaxMip: Float;
  public native let billboardCutoffAlpha: Float;
  public native let aoScale: Float;
  public native let terrainBlendScale: Float;
  public native let terrainBlendBias: Float;
  public native let billboardDepthScale: Float;
  public native let billboardRoughnessBias: Float;
  public native let colorGradient: ResourceRef; // rRef<CGradient>
  public native let colorGradientWeight: Float;
  public native let colorGradientDarkenWeight: Float;
  public native let preserveOriginalColor: Float;
}
