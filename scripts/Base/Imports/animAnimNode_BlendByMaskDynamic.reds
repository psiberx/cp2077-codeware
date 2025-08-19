public native class animAnimNode_BlendByMaskDynamic extends animAnimNode_Base {
  public native let base: animPoseLink;
  public native let blend: animPoseLink;
  public native let mask: animIntLink;
  public native let weight: animFloatLink;
  public native let masks: array<CName>;
  public native let syncMethod: ref<animISyncMethod>;
}
