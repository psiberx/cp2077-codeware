public native class scnChoiceNodeNsAdaptiveLookAtParams extends scnChoiceNodeNsLookAtParams {
  public native let nearbySlotName: CName;
  public native let distantSlotName: CName;
  public native let blendLimit: Float;
  public native let referencePointFullEffectAngle: Float;
  public native let referencePointNoEffectAngle: Float;
  public native let referencePointFullEffectDistance: Float;
  public native let referencePointNoEffectDistance: Float;
  public native let referencePoints: array<scnChoiceNodeNsAdaptiveLookAtReferencePoint>;
  public native let auxiliaryRelativePoint: Vector3;
}
