public native class worldEffect extends resStreamedResource {
  public native let name: CName;
  public native let length: Float;
  public native let inputParameterNames: array<CName>;
  public native let trackRoot: ref<effectTrackGroup>;
  public native let events: array<ref<effectTrackItem>>;
  public native let effectLoops: array<effectLoopData>;
}
