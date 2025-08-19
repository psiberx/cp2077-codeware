public native class animAnimNode_Ik2Constraint extends animAnimNode_OnePoseInput {
  public native let inputTarget: ref<animIAnimNodeSourceChannel_Vector>;
  public native let inputPoleVector: ref<animIAnimNodeSourceChannel_Vector>;
  public native let inputTargetOrientation: ref<animAnimNodeSourceChannel_WeightedQuat>;
  public native let firstBoneIndex: animTransformIndex;
  public native let secondBoneIndex: animTransformIndex;
  public native let endBoneIndex: animTransformIndex;
  public native let hingeAxis: animAxis;
  public native let twistValue: Float;
  public native let weight: Float;
  public native let weightFloatTrack: animNamedTrackIndex;
  public native let weightNode: animFloatLink;
  public native let twistNode: animFloatLink;
  public native let maxHingeAngle: Float;
}
