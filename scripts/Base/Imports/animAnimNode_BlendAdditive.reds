public native class animAnimNode_BlendAdditive extends animAnimNode_Base {
  public native let biasValue: Float;
  public native let scaleValue: Float;
  public native let additiveType: animEAnimGraphAdditiveType;
  public native let timeWarpingEnabled: Bool;
  public native let blendTracks: animEBlendTracksMode;
  public native let syncMethod: ref<animISyncMethod>;
  public native let inputNode: animPoseLink;
  public native let addedInputNode: animPoseLink;
  public native let weightNode: animFloatLink;
  public native let postProcess: ref<animIAnimNode_PostProcess>;
  public native let weightPreviousFrameFloatTrack: animNamedTrackIndex;
  public native let weightPreviousFrameFloatTrackDefaultValue: Float;
  public native let maskName: CName;
}
