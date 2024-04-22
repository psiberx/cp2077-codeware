public native class audioFoleyNPCAppearanceMappingMetadata extends audioAudioMetadata {
  native let fallbackMetadata: CName;
  native let NPCsPerAppearance: array<audioAppearanceToNPCMetadata>;
  native let NPCsPerMainMaterial: array<audioVisualTagToNPCMetadata>;
  native let NPCsPerAdditive: array<audioVisualTagToNPCMetadata>;
}
