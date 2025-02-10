@neverRef() public native class CFoliageProfile extends CResource {
  native let cutoffAlphaMinMip: Float;
  native let cutoffAlphaMaxMip: Float;
  native let billboardCutoffAlpha: Float;
  native let aoScale: Float;
  native let terrainBlendScale: Float;
  native let terrainBlendBias: Float;
  native let billboardDepthScale: Float;
  native let billboardRoughnessBias: Float;
  native let colorGradient: ResourceRef; // rRef<CGradient>
  native let colorGradientWeight: Float;
  native let colorGradientDarkenWeight: Float;
  native let preserveOriginalColor: Float;
}

