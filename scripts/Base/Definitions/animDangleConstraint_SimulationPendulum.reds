public native class animDangleConstraint_SimulationPendulum extends animDangleConstraint_SimulationSingleBone {
  native let constraintType: animPendulumConstraintType;
  native let halfOfMaxApertureAngle: Float;
  native let mass: Float;
  native let damping: Float;
  native let pullForceFactor: Float;
  native let pullForceDirectionLS: Vector3;
  native let externalForceWS: Vector3;
  native let externalForceWsLink: animVectorLink;
  native let collisionCapsuleRadius: Float;
  native let collisionCapsuleHeightExtent: Float;
  native let cosOfHalfMaxApertureAngle: Float;
  native let cosOfHalfOfHalfMaxApertureAngle: Float;
  native let sinOfHalfOfHalfMaxApertureAngle: Float;
  native let invertedMass: Float;
  native let simulationFps: Float;
  native let gravityWS: Float;
  native let projectionType: animPendulumProjectionType;
  native let constraintOrientation: Vector3;
  native let cosOfHalfXAngle: Float;
  native let cosOfHalfYAngle: Float;
  native let cosOfHalfZAngle: Float;
  native let sinOfHalfXAngle: Float;
  native let sinOfHalfYAngle: Float;
  native let sinOfHalfZAngle: Float;
}
