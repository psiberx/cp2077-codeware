public native struct gameMuppetMoveState {
  native let desiredSpeed: Float;
  native let isJumping: Bool;
  native let isFalling: Bool;
  native let isDoubleJumped: Bool;
  native let moveStyle: gameMuppetMoveStyle;
  native let jumpStartFrameId: Uint32;
  native let landFrameId: Uint32;
}
