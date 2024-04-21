public native class ThreatValid extends AIEvent {
  native let owner: wref<Entity>;
  native let threat: wref<Entity>;
  native let isEnemy: Bool;
  native let isHostile: Bool;
}
