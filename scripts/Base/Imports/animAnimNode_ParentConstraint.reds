public native class animAnimNode_ParentConstraint extends animAnimNode_OnePoseInput {
  native let isParentTransformResaved: Bool;
  native let parentTransformIndex: animTransformIndex;
  native let transformIndex: animTransformIndex;
  native let interpolationType: animEInterpolationType;
  native let weight: Float;
  native let weightFloatTrack: animNamedTrackIndex;
  native let useBoneReferencePoseAsDefaultOffset: Bool;
  native let weightNode: animFloatLink;
  native let offsetTranslationLS: animVectorLink;
  native let offsetEulerRotationLS: animVectorLink;
}
