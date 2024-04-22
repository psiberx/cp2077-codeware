public native class animAnimNode_BlendSpace extends animAnimNode_Base {
  native let inputLinks: array<animFloatLink>;
  native let blendSpace: animAnimNode_BlendSpace_InternalsBlendSpace;
  native let progressLink: animFloatLink;
  native let fireAnimEndEvent: Bool;
  native let animEndEventName: CName;
  native let isLooped: Bool;
}
