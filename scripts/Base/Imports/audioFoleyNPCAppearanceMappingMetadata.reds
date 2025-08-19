@mixedRef()
public native class audioFoleyNPCAppearanceMappingMetadata extends audioAudioMetadata {
  public native let fallbackMetadata: CName;
  public native let NPCsPerAppearance: array<audioAppearanceToNPCMetadata>;
  public native let NPCsPerMainMaterial: array<audioVisualTagToNPCMetadata>;
  public native let NPCsPerAdditive: array<audioVisualTagToNPCMetadata>;
}
