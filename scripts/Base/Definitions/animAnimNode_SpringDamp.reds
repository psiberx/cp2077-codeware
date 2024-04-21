public native class animAnimNode_SpringDamp extends animAnimNode_FloatValue {
  native let massFactor: Float;
  native let springFactor: Float;
  native let dampFactor: Float;
  native let startFromDefaultValue: Bool;
  native let defaultInitialValue: Float;
  native let wrapAroundRange: Bool;
  native let rangeMin: Float;
  native let rangeMax: Float;
  native let timeStep: Float;
  native let inputNode: animFloatLink;
}
