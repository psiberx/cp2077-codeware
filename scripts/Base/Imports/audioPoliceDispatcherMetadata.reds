@mixedRef()
public native class audioPoliceDispatcherMetadata extends audioAudioMetadata {
  public native let regularInputs: array<CName>;
  public native let playerChaseStartInputs: array<CName>;
  public native let playerChaseBackupNeededInputs: array<CName>;
  public native let playerChaseEndInputs: array<CName>;
  public native let dispatcherTimeInterval: Float;
  public native let sceneFilePath: String;
}
