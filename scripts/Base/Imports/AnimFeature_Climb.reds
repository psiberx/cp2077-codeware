public native class AnimFeature_Climb extends AnimFeature {
  public native let verticalPosition: Vector4;
  public native let horizontalPosition: Vector4;
  public native let toVerticalTime: Float;
  public native let verticalToHorizontalTime: Float;
  public native let frontEdgePosition: Vector4;
  public native let frontEdgeNormal: Vector4;
  public native let yawAngle: Float;
  public native let stateLength: Float;
  public native let climbType: Int32;
  public native let state: Int32;

  public final native func SetFrontEdgeNormal()
  public final native func SetFrontEdgePosition()
  public final native func SetHorizontalPosition()
  public final native func SetVerticalPosition()
  public final native func SetVerticalToHorizontalTime()
}
