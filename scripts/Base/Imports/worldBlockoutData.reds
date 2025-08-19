public native class worldBlockoutData extends ISerializable {
  public native let points: array<worldBlockoutPoint>;
  public native let edges: array<worldBlockoutEdge>;
  public native let areas: array<worldBlockoutArea>;
  public native let worldSize: Vector2;
  public native let freePoints: array<Uint32>;
  public native let freeEdges: array<Uint32>;
  public native let freeAreas: array<Uint32>;
}
