public native struct animDyngParticle {
  native let mass: Float;
  native let damping: Float;
  native let pullForceFactor: Float;
  native let isFree: Bool;
  native let bone: animTransformIndex;
  native let collisionCapsuleRadius: Float;
  native let collisionCapsuleHeightExtent: Float;
  native let collisionCapsuleAxisLS: Vector3;
  native let projectionType: animDyngParticleProjectionType;
}
