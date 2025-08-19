@neverRef()
public native class worldBlockoutPoint extends ISerializable {
  public native let position: Vector2;
  public native let edges: array<Uint32>;
  public native let constraint: Int32;
  public native let isFree: Bool;
}
