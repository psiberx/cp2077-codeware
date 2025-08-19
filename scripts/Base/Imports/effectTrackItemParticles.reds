public native class effectTrackItemParticles extends effectTrackItem {
  public native let particleSystem: ResourceRef; // rRef<CParticleSystem>
  public native let emissionScale: effectEffectParameterEvaluatorFloat;
  public native let alpha: effectEffectParameterEvaluatorFloat;
  public native let size: effectEffectParameterEvaluatorFloat;
  public native let velocity: effectEffectParameterEvaluatorFloat;
  public native let soundPositionName: CName;
  public native let soundPositionOffset: Vector3;
}
