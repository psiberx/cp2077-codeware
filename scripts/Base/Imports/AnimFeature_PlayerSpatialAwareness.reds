public native class AnimFeature_PlayerSpatialAwareness extends AnimFeature {
  public native let leftClosestVector: Vector4;
  public native let rightClosestVector: Vector4;
  public native let upHitPosition: Vector4;
  public native let forwardDistance: Float;

  public final native func SetForwardDistance()
  public final native func SetLeftClosestVector()
  public final native func SetRightClosestVector()
  public final native func SetSetUpHitPosition()
}
