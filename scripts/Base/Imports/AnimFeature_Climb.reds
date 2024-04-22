public native class AnimFeature_Climb extends AnimFeature {
  native let verticalPosition: Vector4;
  native let horizontalPosition: Vector4;
  native let toVerticalTime: Float;
  native let verticalToHorizontalTime: Float;
  native let frontEdgePosition: Vector4;
  native let frontEdgeNormal: Vector4;
  native let yawAngle: Float;
  native let stateLength: Float;
  native let climbType: Int32;
  native let state: Int32;

  public final native func SetFrontEdgeNormal()
  public final native func SetFrontEdgePosition()
  public final native func SetHorizontalPosition()
  public final native func SetVerticalPosition()
  public final native func SetVerticalToHorizontalTime()
}
