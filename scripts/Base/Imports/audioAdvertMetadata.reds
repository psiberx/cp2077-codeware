public native class audioAdvertMetadata extends audioEmitterMetadata {
  native let advertSoundNames: array<CName>;
  native let minSilenceTime: Float;
  native let maxSilenceTime: Float;
  native let minDistance: Float;
  native let filter: audioAdvertIndoorFilter;
}
