public native class animAnimNode_BlendOverride extends animAnimNode_Base {
  public native let inputNode: animPoseLink;
  public native let overrideInputNode: animPoseLink;
  public native let weightNode: animFloatLink;
  public native let bones: array<animOverrideBlendBoneInfo>;
  public native let blendAllTracks: Bool;
  public native let blendTrackMode: animEBlendTracksMode;
  public native let tracks: array<animOverrideBlendTrackInfo>;
  public native let getDeltaMotionFromOverride: Bool;
  public native let timeWarpingEnabled: Bool;
  public native let syncMethod: ref<animISyncMethod>;
  public native let blendMethod: ref<animIPoseBlendMethod>;
  public native let postProcess: ref<animIAnimNode_PostProcess>;
}
