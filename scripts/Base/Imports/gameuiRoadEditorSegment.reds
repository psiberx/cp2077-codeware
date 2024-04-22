public native struct gameuiRoadEditorSegment {
  native let length: Uint32;
  native let curve: Float;
  native let hasCheckpoint: Bool;
  native let obstacleSettings: array<gameuiRoadEditorObstacleSettings>;
  native let decorationSettings: array<gameuiRoadEditorDecorationSettings>;
}
