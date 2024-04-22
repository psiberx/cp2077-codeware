public native class effectTrackItemParticles extends effectTrackItem {
  native let particleSystem: ResourceRef; // rRef<CParticleSystem>
  native let emissionScale: effectEffectParameterEvaluatorFloat;
  native let alpha: effectEffectParameterEvaluatorFloat;
  native let size: effectEffectParameterEvaluatorFloat;
  native let velocity: effectEffectParameterEvaluatorFloat;
  native let soundPositionName: CName;
  native let soundPositionOffset: Vector3;
}
