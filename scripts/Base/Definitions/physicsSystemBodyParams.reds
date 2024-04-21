public native struct physicsSystemBodyParams {
  native let simulationType: physicsSimulationType;
  native let linearDamping: Float;
  native let angularDamping: Float;
  native let solverIterationsCountPosition: Uint32;
  native let solverIterationsCountVelocity: Uint32;
  native let maxDepenetrationVelocity: Float;
  native let maxAngularVelocity: Float;
  native let maxContactImpulse: Float;
  native let mass: Float;
  native let inertia: Vector3;
  native let comOffset: Transform;
}
