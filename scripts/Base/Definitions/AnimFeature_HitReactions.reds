public native class AnimFeature_HitReactions extends AnimFeature {
  native let hitDirection: Vector4;
  native let hitIntensity: Float;
  native let hitType: Int32;
  native let hitBodyPart: Int32;

  public final native func Hit()
}
