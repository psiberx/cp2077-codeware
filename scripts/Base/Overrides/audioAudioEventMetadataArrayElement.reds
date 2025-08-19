// TODO: Remove after redscript 1.0 release
public native struct audioAudioEventMetadataArrayElement {
  public native let redId: CName;
  public native let wwiseId: Uint32;
  public native let maxAttenuation: Float;
  public native let minDuration: Float;
  public native let maxDuration: Float;
  public native let isLooping: Bool;
  public native let stopActionEvents: array<CName>;
  public native let tags: array<CName>;
}
