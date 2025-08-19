@mixedRef()
public native class audioParamMixerDecoratorMetadata extends audioEmitterMetadata {
  public native let inParams: array<audioMixParamDescription>;
  public native let outputName: CName;
  public native let operation: audioMixParamsAction;
  public native let globalOutput: Bool;
}
