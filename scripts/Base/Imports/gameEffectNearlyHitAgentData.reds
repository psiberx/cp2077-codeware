public native struct gameEffectNearlyHitAgentData {
  public native let hitPosition: Vector4;
  public native let hitDirection: Vector4;
  public native let entity: wref<Entity>;
  public native let isPlayer: Bool;
  public native let wasHit: Bool;
}
