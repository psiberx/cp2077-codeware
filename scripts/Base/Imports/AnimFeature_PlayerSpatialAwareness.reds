public native class AnimFeature_PlayerSpatialAwareness extends AnimFeature {
  native let leftClosestVector: Vector4;
  native let rightClosestVector: Vector4;
  native let upHitPosition: Vector4;
  native let forwardDistance: Float;

  public final native func SetForwardDistance()
  public final native func SetLeftClosestVector()
  public final native func SetRightClosestVector()
  public final native func SetSetUpHitPosition()
}
