public native class CParticleModificatorVelocityTurbulize extends IParticleModificator {
  native let scale: ref<IEvaluatorVector>;
  native let timelifeLimit: ref<IEvaluatorFloat>;
  native let noiseInterval: Float;
  native let duration: Float;
  native let worldSpace: Bool;
}
