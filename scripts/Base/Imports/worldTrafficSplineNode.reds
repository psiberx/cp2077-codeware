public native class worldTrafficSplineNode extends worldTrafficSourceNode {
  native let usage: worldTrafficSplineNodeUsage;
  native let maxSlotMaxSpeed: Float;
  native let width: Float;
  native let pathSamplingDistance: Float;
  native let bidirectional: Bool;
  native let autoConnectionRange: Float;
  native let markings: array<CName>;
  native let outLanes: array<worldTrafficLaneExitDefinition>;
  native let lights: array<worldTrafficLightDefinition>;
  native let neverDeadEnd: Bool;
  native let trafficDisabled: Bool;
  native let laneSamplingAngle: Float;
  native let noAIDriving: Bool;
  native let noAutodrive: Bool;
}
