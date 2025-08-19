public native struct physicsSystemBodyParams {
  public native let simulationType: physicsSimulationType;
  public native let linearDamping: Float;
  public native let angularDamping: Float;
  public native let solverIterationsCountPosition: Uint32;
  public native let solverIterationsCountVelocity: Uint32;
  public native let maxDepenetrationVelocity: Float;
  public native let maxAngularVelocity: Float;
  public native let maxContactImpulse: Float;
  public native let mass: Float;
  public native let inertia: Vector3;
  public native let comOffset: Transform;
}
