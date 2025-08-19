@mixedRef()
public native class audioAcousticsEmitterMetadata extends audioEmitterMetadata {
  public native let obstuctionEnabled: Bool;
  public native let occlusionEnabled: Bool;
  public native let repositioningEnabled: Bool;
  public native let obstructionFadeTime: Float;
  public native let enableOutdoorness: Bool;
  public native let postDopplerFactor: Bool;
  public native let dopplerParameter: CName;
  public native let ignoreOcclusionRadius: Float;
  public native let elevateSource: Bool;
  public native let leakingFloorHack: Bool;
}
