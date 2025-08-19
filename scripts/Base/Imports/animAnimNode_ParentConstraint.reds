public native class animAnimNode_ParentConstraint extends animAnimNode_OnePoseInput {
  public native let parentTransform: ref<animIAnimNodeSourceChannel_QsTransform>;
  public native let isParentTransformResaved: Bool;
  public native let parentTransformIndex: animTransformIndex;
  public native let transformIndex: animTransformIndex;
  public native let interpolationType: animEInterpolationType;
  public native let weight: Float;
  public native let weightFloatTrack: animNamedTrackIndex;
  public native let useBoneReferencePoseAsDefaultOffset: Bool;
  public native let weightNode: animFloatLink;
  public native let offsetTranslationLS: animVectorLink;
  public native let offsetEulerRotationLS: animVectorLink;
}
