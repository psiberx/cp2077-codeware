public native struct animDyngParticle {
  public native let mass: Float;
  public native let damping: Float;
  public native let pullForceFactor: Float;
  public native let isFree: Bool;
  public native let bone: animTransformIndex;
  public native let collisionCapsuleRadius: Float;
  public native let collisionCapsuleHeightExtent: Float;
  public native let collisionCapsuleAxisLS: Vector3;
  public native let projectionType: animDyngParticleProjectionType;
}
