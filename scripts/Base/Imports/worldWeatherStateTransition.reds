public native class worldWeatherStateTransition extends ISerializable {
  public native let probability: CurveDataFloat;
  public native let transitionDuration: CurveDataFloat;
  public native let sourceWeatherState: ref<worldWeatherState>;
  public native let targetWeatherState: ref<worldWeatherState>;
}
