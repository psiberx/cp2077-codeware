public native struct rendRenderParticleUpdaterData {
  native let modifOffset: Uint32;
  native let animFrameInit: array<Float>;
  native let turbulenceNoiseInterval: Float;
  native let turbulenceDuration: Float;
  native let collisionMask: Uint64;
  native let collisionDynamicFriction: Float;
  native let collisionStaticFriction: Float;
  native let collisionRestitution: Float;
  native let collisionVelocityDamp: Float;
  native let collisionDisableGravity: Bool;
  native let collisionRadius: Float;
  native let collisionEffectMask: Uint32;
  native let maxCollisions: Uint8;
  native let eventGenerate: CName;
  native let eventReceive: CName;
  native let eventFrequency: Float;
  native let eventProbability: Float;
  native let noiseType: Uint8;
  native let randomPerChannel: Bool;
  native let eventSpawnObject: Uint8;
}
