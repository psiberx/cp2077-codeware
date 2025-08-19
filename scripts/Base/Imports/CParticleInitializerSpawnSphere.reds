public native class CParticleInitializerSpawnSphere extends IParticleInitializer {
  public native let innerRadius: ref<IEvaluatorFloat>;
  public native let outerRadius: ref<IEvaluatorFloat>;
  public native let surfaceOnly: Bool;
  public native let spawnPositiveX: Bool;
  public native let spawnNegativeX: Bool;
  public native let spawnPositiveY: Bool;
  public native let spawnNegativeY: Bool;
  public native let spawnPositiveZ: Bool;
  public native let spawnNegativeZ: Bool;
  public native let velocity: Bool;
  public native let worldSpace: Bool;
  public native let forceScale: ref<IEvaluatorFloat>;
}
