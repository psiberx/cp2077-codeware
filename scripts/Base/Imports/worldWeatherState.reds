public native class worldWeatherState extends ISerializable {
  native let minDuration: CurveDataFloat;
  native let maxDuration: CurveDataFloat;
  native let environmentAreaParameters: ResourceRef; // rRef<worldEnvironmentAreaParameters>
  native let effect: ResourceAsyncRef; // raRef<worldEffect>
  native let name: CName;
  native let probability: CurveDataFloat;
  native let transitionDuration: CurveDataFloat;
}
