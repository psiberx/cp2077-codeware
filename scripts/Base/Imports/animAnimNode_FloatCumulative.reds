public native class animAnimNode_FloatCumulative extends animAnimNode_FloatValue {
  public native let clamp: Bool;
  public native let resetOnActivation: Bool;
  public native let normalize180: Bool;
  public native let defaultValue: Float;
  public native let resetExternalEventName: CName;
  public native let inputNode: animFloatLink;
  public native let minValue: animFloatLink;
  public native let maxValue: animFloatLink;
  public native let resetSpeed: animFloatLink;
  public native let override: animBoolLink;
  public native let curValue: animFloatLink;
  public native let normalize180Input: animBoolLink;
}
