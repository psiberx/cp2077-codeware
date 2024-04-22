public native class audioGroupingTagMetadata extends audioAudioMetadata {
  native let shape: CName;
  native let classificationMethod: audioClassificationMethod;
  native let inputEmitterName: CName;
  native let inputEventNames: array<CName>;
  native let inputTags: array<CName>;
  native let outputEventId: CName;
  native let minimalGroupCount: Float;
  native let fullGroupCount: Float;
}
