public native class animAnimNode_BlendOverride extends animAnimNode_Base {
  native let inputNode: animPoseLink;
  native let overrideInputNode: animPoseLink;
  native let weightNode: animFloatLink;
  native let bones: array<animOverrideBlendBoneInfo>;
  native let blendAllTracks: Bool;
  native let blendTrackMode: animEBlendTracksMode;
  native let tracks: array<animOverrideBlendTrackInfo>;
  native let getDeltaMotionFromOverride: Bool;
  native let timeWarpingEnabled: Bool;
}
