public native struct gameEffectNearlyHitAgentData {
  native let hitPosition: Vector4;
  native let hitDirection: Vector4;
  native let entity: wref<Entity>;
  native let isPlayer: Bool;
  native let wasHit: Bool;
}
