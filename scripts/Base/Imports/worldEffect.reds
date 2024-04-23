public native class worldEffect extends resStreamedResource {
  native let name: CName;
  native let length: Float;
  native let inputParameterNames: array<CName>;
  native let trackRoot: ref<effectTrackGroup>;
  native let events: array<ref<effectTrackItem>>;
  native let effectLoops: array<effectLoopData>;
}
