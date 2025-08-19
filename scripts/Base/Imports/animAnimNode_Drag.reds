public native class animAnimNode_Drag extends animAnimNode_OnePoseInput {
  public native let sourceBone: animTransformIndex;
  public native let outTargetBone: animTransformIndex;
  public native let simulationFps: Float;
  public native let sourceSpeedMultiplier: Float;
  public native let hasOvershoot: Bool;
  public native let overshootDuration: Float;
  public native let overshootDetectionMinSpeed: Float;
  public native let overshootDetectionMaxSpeed: Float;
  public native let useSteps: Bool;
  public native let stepsTargetSpeedMultiplier: Float;
  public native let timeBetweenSteps: Float;
  public native let timeInStep: Float;
}
