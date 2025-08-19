@mixedRef()
public native class audioGroupingTagMetadata extends audioAudioMetadata {
  public native let shape: CName;
  public native let classificationMethod: audioClassificationMethod;
  public native let inputEmitterName: CName;
  public native let inputEventNames: array<CName>;
  public native let inputTags: array<CName>;
  public native let outputEventId: CName;
  public native let minimalGroupCount: Float;
  public native let fullGroupCount: Float;
}
