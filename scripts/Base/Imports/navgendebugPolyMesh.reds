@neverRef()
public native class navgendebugPolyMesh extends ISerializable {
  public native let vertices: array<Vector3>;
  public native let polygons: array<navgendebugCompactPolygon>;
  public native let bounds: Box;
  public native let cellSize: Float;
  public native let cellHeight: Float;
  public native let borderSize: Int32;
  public native let maxEdgeError: Float;
  public native let maxVerticesPerPolygon: Int32;
}
