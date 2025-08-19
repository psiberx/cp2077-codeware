public native class animAnimNode_FootStepAdjuster extends animAnimNode_OnePoseInput {
  public native let leftToeName: animTransformIndex;
  public native let rightToeName: animTransformIndex;
  public native let leftFootName: animTransformIndex;
  public native let rightFootName: animTransformIndex;
  public native let leftCalfName: animTransformIndex;
  public native let rightCalfName: animTransformIndex;
  public native let leftThighName: animTransformIndex;
  public native let rightThighName: animTransformIndex;
  public native let pelvisBoneName: animTransformIndex;
  public native let calfHingeAxis: Vector4;
  public native let IKBlendTime: Float;
  public native let pelvisAdjustmentBlendSpeed: Float;
  public native let adjustPelvisVertically: Bool;
  public native let stepAdjustmentInterval: Float;
  public native let controlValueNode: animFloatLink;
  public native let controlVectorNode: animVectorLink;
}
