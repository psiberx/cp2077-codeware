public native struct gameMuppetMoveState {
  public native let desiredSpeed: Float;
  public native let isJumping: Bool;
  public native let isFalling: Bool;
  public native let isDoubleJumped: Bool;
  public native let moveStyle: gameMuppetMoveStyle;
  public native let jumpStartFrameId: Uint32;
  public native let landFrameId: Uint32;
}
