public native class questCharacterControlledObjectHit_ConditionType extends questICharacterConditionType {
  native let attackerRef: EntityReference;
  native let targetRef: EntityReference;
  native let isTargetPlayer: Bool;
  native let includeHitTypes: array<questCharacterHitEventType>;
  native let excludeHitTypes: array<questCharacterHitEventType>;
  native let includeHitShapes: array<CName>;
  native let excludeHitShapes: array<CName>;
}
