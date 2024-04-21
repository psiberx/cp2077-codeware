public native class audioAudioSceneData extends audioAudioMetadata {
  native let states: array<audioAudioStateData>;
  native let anyStateTransitionsTable: array<audioAnyStateTransitionEntry>;
  native let voLineSignals: array<audioVoLineSignal>;
  native let signalLeadingToShutdown: CName;
  native let templateScene: CName;
  native let templateSceneStateOverrides: array<audioAudioSceneStateOverride>;
  native let templateSceneSignalOverrides: array<audioAudioSceneSignalOverride>;
}
