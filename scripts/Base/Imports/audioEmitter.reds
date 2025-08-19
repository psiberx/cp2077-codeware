public native class audioEmitter extends IPlacedComponent {
  public native let EmitterName: CName;
  public native let EmitterType: audioEntityEmitterContextType;
  public native let OnAttach: gameAudioSyncs;
  public native let OnDetach: gameAudioSyncs;
  public native let updateDistance: Float;
  public native let emitterMetadataName: CName;
  public native let Tags: array<CName>;
  public native let TagList: redTagList;
}
