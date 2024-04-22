public native class questCharacterHit_ConditionType extends questICharacterConditionType {
  native let attackerRef: EntityReference;
  native let isAttackerPlayer: Bool;
  native let targetRef: EntityReference;
  native let isTargetPlayer: Bool;
  native let includeHitTypes: array<questCharacterHitEventType>;
  native let excludeHitTypes: array<questCharacterHitEventType>;
  native let includeHitShapes: array<CName>;
  native let excludeHitShapes: array<CName>;
}
