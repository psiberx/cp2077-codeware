public native class GeometryShape extends ISerializable {
  public native let vertices: array<Vector3>;
  public native let indices: array<Uint16>;
  public native let faces: array<GeometryShapeFace>;
}
