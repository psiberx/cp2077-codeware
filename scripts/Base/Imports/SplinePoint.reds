public native struct SplinePoint {
  public native let position: Vector3;
  public native let rotation: Quaternion;
  public native let tangents: [Vector3; 2];
  public native let continuousTangents: Bool;
  public native let automaticTangents: Bool;
  public native let id: Uint32;
}
