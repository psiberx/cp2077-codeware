public native class worldBlockoutArea extends ISerializable {
  native let name: String;
  native let color: Color;
  native let parent: Uint32;
  native let children: array<Uint32>;
  native let isFree: Bool;
  native let increaseTerrainStreamingDistance: Bool;
}
