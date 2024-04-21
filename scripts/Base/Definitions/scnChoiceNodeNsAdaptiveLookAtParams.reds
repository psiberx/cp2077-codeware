public native class scnChoiceNodeNsAdaptiveLookAtParams extends scnChoiceNodeNsLookAtParams {
  native let nearbySlotName: CName;
  native let distantSlotName: CName;
  native let blendLimit: Float;
  native let referencePointFullEffectAngle: Float;
  native let referencePointNoEffectAngle: Float;
  native let referencePointFullEffectDistance: Float;
  native let referencePointNoEffectDistance: Float;
  native let referencePoints: array<scnChoiceNodeNsAdaptiveLookAtReferencePoint>;
  native let auxiliaryRelativePoint: Vector3;
}
