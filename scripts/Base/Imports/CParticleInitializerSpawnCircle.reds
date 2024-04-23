public native class CParticleInitializerSpawnCircle extends IParticleInitializer {
  native let innerRadius: ref<IEvaluatorFloat>;
  native let outerRadius: ref<IEvaluatorFloat>;
  native let surfaceOnly: Bool;
  native let worldSpace: Bool;
  native let spawnToLocal: Matrix;
}
