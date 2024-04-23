public native class CParticleSystem extends resStreamedResource {
  native let visibleThroughWalls: Bool;
  native let prewarmingTime: Float;
  native let emitters: array<ref<CParticleEmitter>>;
  native let boundingBox: Box;
  native let autoHideDistance: Float;
  native let autoHideRange: Float;
  native let lastLODFadeoutRange: Float;
  native let renderingPlane: ERenderingPlane;
  native let particleDamage: ref<ParticleDamage>;
}
