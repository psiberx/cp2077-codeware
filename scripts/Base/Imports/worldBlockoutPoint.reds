@neverRef()
public native class worldBlockoutPoint extends ISerializable {
  native let position: Vector2;
  native let edges: array<Uint32>;
  native let constraint: Int32;
  native let isFree: Bool;
}
