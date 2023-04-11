public native class gameAudioEmitterComponent extends IPlacedComponent {
  native let EmitterName: CName;
  native let EmitterType: audioEntityEmitterContextType;
  native let OnAttach: gameAudioSyncs;
  native let OnDetach: gameAudioSyncs;
  native let updateDistance: Float;
  native let emitterMetadataName: CName;
  native let Tags: array<CName>;
  native let TagList: TagList;
}
