public native class animAnimNode_DampFloat extends animAnimNode_FloatValue {
  native let defaultIncreaseSpeed: Float;
  native let defaultDecreaseSpeed: Float;
  native let startFromDefaultValue: Bool;
  native let defaultInitialValue: Float;
  native let wrapAroundRange: Bool;
  native let rangeMin: Float;
  native let rangeMax: Float;
  native let inputNode: animFloatLink;
  native let increaseSpeedNode: animFloatLink;
  native let decreaseSpeedNode: animFloatLink;
}
