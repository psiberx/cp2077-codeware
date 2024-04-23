public native class animAnimNode_BlendAdditive extends animAnimNode_Base {
  native let biasValue: Float;
  native let scaleValue: Float;
  native let additiveType: animEAnimGraphAdditiveType;
  native let timeWarpingEnabled: Bool;
  native let blendTracks: animEBlendTracksMode;
  native let syncMethod: ref<animISyncMethod>;
  native let inputNode: animPoseLink;
  native let addedInputNode: animPoseLink;
  native let weightNode: animFloatLink;
  native let postProcess: ref<animIAnimNode_PostProcess>;
  native let weightPreviousFrameFloatTrack: animNamedTrackIndex;
  native let weightPreviousFrameFloatTrackDefaultValue: Float;
  native let maskName: CName;
}
