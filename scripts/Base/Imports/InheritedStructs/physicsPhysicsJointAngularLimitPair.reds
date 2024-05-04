public native struct physicsPhysicsJointAngularLimitPair {
  native let restitution: Float;
  native let bounceThreshold: Float;
  native let stiffness: Float;
  native let damping: Float;
  native let contactDistance: Float;

  native let twist: physicsPhysicsJointMotion;
  native let upper: Float;
  native let lower: Float;
}
