@mixedRef()
public abstract native class audioEntitySettings extends audioAudioMetadata {
  public native let commonSettings: audioCommonEntitySettings;
  public native let scanningSettings: audioScanningSettings;
  public native let auxiliaryMetadata: audioAuxiliaryMetadata;
  public native let emitterDecoratorMetadata: CName;
  public native let preferSoundComponentPosition: Bool;
}
