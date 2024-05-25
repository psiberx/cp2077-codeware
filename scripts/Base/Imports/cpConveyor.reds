public native class cpConveyor extends GameObject {
  native let lines: array<cpConveyorLine>;
  native let movementCurve: CurveDataFloat;
  native let entityDistance: Float;
  native let entitySpawnOffset: Float;
  native let audioParameterLineActive: CName;
  native let audioParameterLineCycle: CName;
  native let audioParameterLineSpeed: CName;
}
