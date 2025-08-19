public native class CParticleModificatorNoise extends IParticleModificator {
  public native let amplitude: ref<IEvaluatorVector>;
  public native let offset: ref<IEvaluatorVector>;
  public native let frequency: ref<IEvaluatorVector>;
  public native let changeRate: Vector3;
  public native let applyToPosition: Bool;
  public native let worldSpaceOffset: Bool;
  public native let noiseType: ENoiseType;
}
