public native class animAnimNode_SpringDamp extends animAnimNode_FloatValue {
  public native let massFactor: Float;
  public native let springFactor: Float;
  public native let dampFactor: Float;
  public native let startFromDefaultValue: Bool;
  public native let defaultInitialValue: Float;
  public native let wrapAroundRange: Bool;
  public native let rangeMin: Float;
  public native let rangeMax: Float;
  public native let timeStep: Float;
  public native let inputNode: animFloatLink;
}
