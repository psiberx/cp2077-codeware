public native class CParticleModificatorCollision extends IParticleModificator {
  native let restitution: Float;
  native let dynamicFriction: Float;
  native let staticFriction: Float;
  native let velocityDamp: Float;
  native let angularVelocityDamp: Float;
  native let particleMass: Float;
  native let particleRadius: Float;
  native let useGPUAcceleration: Bool;
  native let disableGravity: Bool;
  native let killOnCollision: Bool;
}
