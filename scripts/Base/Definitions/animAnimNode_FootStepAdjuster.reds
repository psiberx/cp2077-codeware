public native class animAnimNode_FootStepAdjuster extends animAnimNode_OnePoseInput {
  native let leftToeName: animTransformIndex;
  native let rightToeName: animTransformIndex;
  native let leftFootName: animTransformIndex;
  native let rightFootName: animTransformIndex;
  native let leftCalfName: animTransformIndex;
  native let rightCalfName: animTransformIndex;
  native let leftThighName: animTransformIndex;
  native let rightThighName: animTransformIndex;
  native let pelvisBoneName: animTransformIndex;
  native let calfHingeAxis: Vector4;
  native let IKBlendTime: Float;
  native let pelvisAdjustmentBlendSpeed: Float;
  native let adjustPelvisVertically: Bool;
  native let stepAdjustmentInterval: Float;
  native let controlValueNode: animFloatLink;
  native let controlVectorNode: animVectorLink;
}
