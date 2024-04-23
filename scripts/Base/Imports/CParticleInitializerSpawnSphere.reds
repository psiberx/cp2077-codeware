public native class CParticleInitializerSpawnSphere extends IParticleInitializer {
  native let innerRadius: ref<IEvaluatorFloat>;
  native let outerRadius: ref<IEvaluatorFloat>;
  native let surfaceOnly: Bool;
  native let spawnPositiveX: Bool;
  native let spawnNegativeX: Bool;
  native let spawnPositiveY: Bool;
  native let spawnNegativeY: Bool;
  native let spawnPositiveZ: Bool;
  native let spawnNegativeZ: Bool;
  native let velocity: Bool;
  native let worldSpace: Bool;
  native let forceScale: ref<IEvaluatorFloat>;
}
