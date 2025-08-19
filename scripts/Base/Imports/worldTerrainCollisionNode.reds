public native class worldTerrainCollisionNode extends worldNode {
  public native let materials: array<CName>;
  public native let materialIndices: array<Uint8>;
  public native let actorTransform: WorldTransform;
  public native let extents: Vector4;
  public native let streamingDistance: Float;
  public native let rowScale: Float;
  public native let columnScale: Float;
  public native let heightScale: Float;
  public native let increaseStreamingDistance: Bool;
}
