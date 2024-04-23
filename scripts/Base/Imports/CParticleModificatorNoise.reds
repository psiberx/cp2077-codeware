public native class CParticleModificatorNoise extends IParticleModificator {
  native let amplitude: ref<IEvaluatorVector>;
  native let offset: ref<IEvaluatorVector>;
  native let frequency: ref<IEvaluatorVector>;
  native let changeRate: Vector3;
  native let applyToPosition: Bool;
  native let worldSpaceOffset: Bool;
  native let noiseType: ENoiseType;
}
