public native class animAnimNode_Drag extends animAnimNode_OnePoseInput {
  native let sourceBone: animTransformIndex;
  native let outTargetBone: animTransformIndex;
  native let simulationFps: Float;
  native let sourceSpeedMultiplier: Float;
  native let hasOvershoot: Bool;
  native let overshootDuration: Float;
  native let overshootDetectionMinSpeed: Float;
  native let overshootDetectionMaxSpeed: Float;
  native let useSteps: Bool;
  native let stepsTargetSpeedMultiplier: Float;
  native let timeBetweenSteps: Float;
  native let timeInStep: Float;
}
