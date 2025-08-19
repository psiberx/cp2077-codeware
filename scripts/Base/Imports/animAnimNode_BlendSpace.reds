public native class animAnimNode_BlendSpace extends animAnimNode_Base {
  public native let inputLinks: array<animFloatLink>;
  public native let blendSpace: animAnimNode_BlendSpace_InternalsBlendSpace;
  public native let progressLink: animFloatLink;
  public native let fireAnimEndEvent: Bool;
  public native let animEndEventName: CName;
  public native let isLooped: Bool;
}
