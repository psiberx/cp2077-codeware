public native class animDyngConstraintCone extends animIDyngConstraint {
  native let constrainedBone: animTransformIndex;
  native let coneAttachmentBone: animTransformIndex;
  native let coneTransformLS: QsTransform;
  native let constraintType: animPendulumConstraintType;
  native let halfOfMaxApertureAngle: Float;
  native let projectionType: animPendulumProjectionType;
  native let collisionCapsuleRadius: Float;
  native let collisionCapsuleHeightExtent: Float;
}
