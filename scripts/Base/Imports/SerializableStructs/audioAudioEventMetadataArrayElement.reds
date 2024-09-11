public native struct audioAudioEventMetadataArrayElement {
  native let redId: CName;
  native let wwiseId: Uint32;
  native let maxAttenuation: Float;
  native let minDuration: Float;
  native let maxDuration: Float;
  native let isLooping: Bool;
  native let stopActionEvents: array<CName>;
  native let tags: array<CName>;
}
