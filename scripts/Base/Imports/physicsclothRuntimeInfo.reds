public native struct physicsclothRuntimeInfo {
  native let translation: Vector3;
  native let rotation: Quaternion;
  native let gravity: Vector3;
  native let damping: Float;
  native let drag: Float;
  native let inertia: Float;
  native let numSolverIterations: Uint32;
  native let stiffnessFrequency: Float;
  native let friction: Float;
  native let tetherStiffness: Float;
  native let tetherScale: Float;
  native let selfCollisionDistance: Float;
  native let selfCollisionStiffness: Float;
  native let liftCoefficient: Float;
  native let dragCoefficient: Float;
  native let gravityScale: Float;
  native let motionConstraintStiffness: Float;
  native let enableSelfCollision: Bool;
}
