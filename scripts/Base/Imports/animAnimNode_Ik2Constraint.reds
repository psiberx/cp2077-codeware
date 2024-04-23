public native class animAnimNode_Ik2Constraint extends animAnimNode_OnePoseInput {
  native let inputTarget: ref<animIAnimNodeSourceChannel_Vector>;
  native let inputPoleVector: ref<animIAnimNodeSourceChannel_Vector>;
  native let inputTargetOrientation: ref<animAnimNodeSourceChannel_WeightedQuat>;
  native let firstBoneIndex: animTransformIndex;
  native let secondBoneIndex: animTransformIndex;
  native let endBoneIndex: animTransformIndex;
  native let hingeAxis: animAxis;
  native let twistValue: Float;
  native let weight: Float;
  native let weightFloatTrack: animNamedTrackIndex;
  native let weightNode: animFloatLink;
  native let twistNode: animFloatLink;
  native let maxHingeAngle: Float;
}
