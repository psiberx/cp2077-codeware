public native class worldTerrainCollisionNode extends worldNode {
  native let materials: array<CName>;
  native let materialIndices: array<Uint8>;
  native let actorTransform: WorldTransform;
  native let extents: Vector4;
  native let streamingDistance: Float;
  native let rowScale: Float;
  native let columnScale: Float;
  native let heightScale: Float;
  native let increaseStreamingDistance: Bool;
}
