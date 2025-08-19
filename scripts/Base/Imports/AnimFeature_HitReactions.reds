public native class AnimFeature_HitReactions extends AnimFeature {
  public native let hitDirection: Vector4;
  public native let hitIntensity: Float;
  public native let hitType: Int32;
  public native let hitBodyPart: Int32;

  public final native func Hit()
}
