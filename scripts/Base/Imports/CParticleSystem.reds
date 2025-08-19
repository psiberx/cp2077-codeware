public native class CParticleSystem extends resStreamedResource {
  public native let visibleThroughWalls: Bool;
  public native let prewarmingTime: Float;
  public native let emitters: array<ref<CParticleEmitter>>;
  public native let boundingBox: Box;
  public native let autoHideDistance: Float;
  public native let autoHideRange: Float;
  public native let lastLODFadeoutRange: Float;
  public native let renderingPlane: ERenderingPlane;
  public native let particleDamage: ref<ParticleDamage>;
}
