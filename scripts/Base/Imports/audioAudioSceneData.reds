@mixedRef()
public native class audioAudioSceneData extends audioAudioMetadata {
  public native let anyStateArray: [audioAudioStateData; 1];
  public native let states: array<audioAudioStateData>;
  public native let anyStateTransitionsTable: array<audioAnyStateTransitionEntry>;
  public native let voLineSignals: array<audioVoLineSignal>;
  public native let signalLeadingToShutdown: CName;
  public native let templateScene: CName;
  public native let templateSceneStateOverrides: array<audioAudioSceneStateOverride>;
  public native let templateSceneSignalOverrides: array<audioAudioSceneSignalOverride>;
}
