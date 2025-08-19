public native class animAnimSet extends CResource {
  public native let animations: array<ref<animAnimSetEntry>>;
  public native let animationDataChunks: array<animAnimDataChunk>;
  public native let fallbackDataAddresses: array<Uint16>;
  public native let fallbackDataAddressIndexes: array<Uint8>;
  public native let fallbackAnimFrameDescs: array<animAnimFallbackFrameDesc>;
  public native let fallbackAnimDescIndexes: array<Uint8>;
  public native let fallbackNumPositionData: Uint16;
  public native let fallbackNumRotationData: Uint16;
  public native let fallbackNumFloatTrackData: Uint16;
  public native let rig: ResourceRef; // rRef<animRig>
  public native let tags: redTagList;
  public native let version: Uint32;
}
