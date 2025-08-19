public native class questCharacterHit_ConditionType extends questICharacterConditionType {
  public native let attackerRef: EntityReference;
  public native let isAttackerPlayer: Bool;
  public native let targetRef: EntityReference;
  public native let isTargetPlayer: Bool;
  public native let includeHitTypes: array<questCharacterHitEventType>;
  public native let excludeHitTypes: array<questCharacterHitEventType>;
  public native let includeHitShapes: array<CName>;
  public native let excludeHitShapes: array<CName>;
}
