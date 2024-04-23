public native class animAnimSet extends CResource {
  native let animations: array<ref<animAnimSetEntry>>;
  native let animationDataChunks: array<animAnimDataChunk>;
  native let fallbackDataAddresses: array<Uint16>;
  native let fallbackDataAddressIndexes: array<Uint8>;
  native let fallbackAnimFrameDescs: array<animAnimFallbackFrameDesc>;
  native let fallbackAnimDescIndexes: array<Uint8>;
  native let fallbackNumPositionData: Uint16;
  native let fallbackNumRotationData: Uint16;
  native let fallbackNumFloatTrackData: Uint16;
  native let rig: ResourceRef; // rRef<animRig>
  native let tags: redTagList;
  native let version: Uint32;
}
