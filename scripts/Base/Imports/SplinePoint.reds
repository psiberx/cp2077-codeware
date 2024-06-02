public native struct SplinePoint {
  native let position: Vector3;
  native let rotation: Quaternion;
  native let tangents: [Vector3; 2];
  native let continuousTangents: Bool;
  native let automaticTangents: Bool;
  native let id: Uint32;
}
