public native class ThreatValid extends AIEvent {
  public native let owner: wref<Entity>;
  public native let threat: wref<Entity>;
  public native let isEnemy: Bool;
  public native let isHostile: Bool;
}
