public native class GeometryShape extends ISerializable {
  native let vertices: array<Vector3>;
  native let indices: array<Uint16>;
  native let faces: array<GeometryShapeFace>;
}
