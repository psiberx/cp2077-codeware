public native class worldWeatherStateTransition extends ISerializable {
  native let probability: CurveDataFloat;
  native let transitionDuration: CurveDataFloat;
  native let sourceWeatherState: ref<worldWeatherState>;
  native let targetWeatherState: ref<worldWeatherState>;
}
