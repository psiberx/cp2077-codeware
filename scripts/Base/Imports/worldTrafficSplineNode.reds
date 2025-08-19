public native class worldTrafficSplineNode extends worldTrafficSourceNode {
  public native let usage: worldTrafficSplineNodeUsage;
  public native let maxSlotMaxSpeed: Float;
  public native let width: Float;
  public native let pathSamplingDistance: Float;
  public native let bidirectional: Bool;
  public native let autoConnectionRange: Float;
  public native let markings: array<CName>;
  public native let outLanes: array<worldTrafficLaneExitDefinition>;
  public native let lights: array<worldTrafficLightDefinition>;
  public native let neverDeadEnd: Bool;
  public native let trafficDisabled: Bool;
  public native let laneSamplingAngle: Float;
  public native let noAIDriving: Bool;
  public native let noAutodrive: Bool;
}
