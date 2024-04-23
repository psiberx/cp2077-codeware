public native class worldBlockoutData extends ISerializable {
  native let points: array<worldBlockoutPoint>;
  native let edges: array<worldBlockoutEdge>;
  native let areas: array<worldBlockoutArea>;
  native let worldSize: Vector2;
  native let freePoints: array<Uint32>;
  native let freeEdges: array<Uint32>;
  native let freeAreas: array<Uint32>;
}
