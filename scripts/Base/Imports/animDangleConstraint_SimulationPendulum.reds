public native class animDangleConstraint_SimulationPendulum extends animDangleConstraint_SimulationSingleBone {
  public native let constraintType: animPendulumConstraintType;
  public native let halfOfMaxApertureAngle: Float;
  public native let mass: Float;
  public native let damping: Float;
  public native let pullForceFactor: Float;
  public native let pullForceDirectionLS: Vector3;
  public native let externalForceWS: Vector3;
  public native let externalForceWsLink: animVectorLink;
  public native let collisionCapsuleRadius: Float;
  public native let collisionCapsuleHeightExtent: Float;
  public native let cosOfHalfMaxApertureAngle: Float;
  public native let cosOfHalfOfHalfMaxApertureAngle: Float;
  public native let sinOfHalfOfHalfMaxApertureAngle: Float;
  public native let invertedMass: Float;
  public native let simulationFps: Float;
  public native let gravityWS: Float;
  public native let projectionType: animPendulumProjectionType;
  public native let constraintOrientation: Vector3;
  public native let cosOfHalfXAngle: Float;
  public native let cosOfHalfYAngle: Float;
  public native let cosOfHalfZAngle: Float;
  public native let sinOfHalfXAngle: Float;
  public native let sinOfHalfYAngle: Float;
  public native let sinOfHalfZAngle: Float;
}
