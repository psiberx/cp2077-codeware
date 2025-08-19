public native class CParticleInitializerSpawnCircle extends IParticleInitializer {
  public native let innerRadius: ref<IEvaluatorFloat>;
  public native let outerRadius: ref<IEvaluatorFloat>;
  public native let surfaceOnly: Bool;
  public native let worldSpace: Bool;
  public native let spawnToLocal: Matrix;
}
