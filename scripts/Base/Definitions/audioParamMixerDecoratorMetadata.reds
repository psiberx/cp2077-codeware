public native class audioParamMixerDecoratorMetadata extends audioEmitterMetadata {
  native let inParams: array<audioMixParamDescription>;
  native let outputName: CName;
  native let operation: audioMixParamsAction;
  native let globalOutput: Bool;
}
