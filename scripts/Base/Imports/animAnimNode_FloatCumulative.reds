public native class animAnimNode_FloatCumulative extends animAnimNode_FloatValue {
  native let clamp: Bool;
  native let resetOnActivation: Bool;
  native let normalize180: Bool;
  native let defaultValue: Float;
  native let resetExternalEventName: CName;
  native let inputNode: animFloatLink;
  native let minValue: animFloatLink;
  native let maxValue: animFloatLink;
  native let resetSpeed: animFloatLink;
  native let override: animBoolLink;
  native let curValue: animFloatLink;
  native let normalize180Input: animBoolLink;
}
