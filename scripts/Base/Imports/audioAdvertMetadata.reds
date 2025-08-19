@mixedRef()
public native class audioAdvertMetadata extends audioEmitterMetadata {
  public native let advertSoundNames: array<CName>;
  public native let minSilenceTime: Float;
  public native let maxSilenceTime: Float;
  public native let minDistance: Float;
  public native let filter: audioAdvertIndoorFilter;
}
