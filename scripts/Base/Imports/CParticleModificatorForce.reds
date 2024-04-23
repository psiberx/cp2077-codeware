public native class CParticleModificatorForce extends IParticleModificator {
  native let pivot: Vector3;
  native let radius: Float;
  native let scale: ref<IEvaluatorFloat>;
  native let damp: ref<IEvaluatorVector>;
}
