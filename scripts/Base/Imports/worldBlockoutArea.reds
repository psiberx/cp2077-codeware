@neverRef()
public native class worldBlockoutArea extends ISerializable {
  public native let name: String;
  public native let color: Color;
  public native let parent: Uint32;
  public native let children: array<Uint32>;
  public native let outlines: array<ref<worldBlockoutAreaOutline>>;
  public native let isFree: Bool;
  public native let increaseTerrainStreamingDistance: Bool;
}
