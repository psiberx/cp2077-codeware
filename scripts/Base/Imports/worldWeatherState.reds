public native class worldWeatherState extends ISerializable {
  public native let minDuration: CurveDataFloat;
  public native let maxDuration: CurveDataFloat;
  public native let environmentAreaParameters: ResourceRef; // rRef<worldEnvironmentAreaParameters>
  public native let effect: ResourceAsyncRef; // raRef<worldEffect>
  public native let name: CName;
  public native let probability: CurveDataFloat;
  public native let transitionDuration: CurveDataFloat;
}
