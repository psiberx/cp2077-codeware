public native class audioAcousticsEmitterMetadata extends audioEmitterMetadata {
  native let obstuctionEnabled: Bool;
  native let occlusionEnabled: Bool;
  native let repositioningEnabled: Bool;
  native let obstructionFadeTime: Float;
  native let enableOutdoorness: Bool;
  native let postDopplerFactor: Bool;
  native let dopplerParameter: CName;
  native let ignoreOcclusionRadius: Float;
  native let elevateSource: Bool;
  native let leakingFloorHack: Bool;
}
