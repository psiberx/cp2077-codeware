public native class cpConveyor extends GameObject {
  public native let lines: array<cpConveyorLine>;
  public native let movementCurve: CurveDataFloat;
  public native let entityDistance: Float;
  public native let entitySpawnOffset: Float;
  public native let audioParameterLineActive: CName;
  public native let audioParameterLineCycle: CName;
  public native let audioParameterLineSpeed: CName;
}
