@neverRef()
public native class navgendebugPolyMesh extends ISerializable {
  native let vertices: array<Vector3>;
  native let polygons: array<navgendebugCompactPolygon>;
  native let bounds: Box;
  native let cellSize: Float;
  native let cellHeight: Float;
  native let borderSize: Int32;
  native let maxEdgeError: Float;
  native let maxVerticesPerPolygon: Int32;
}
