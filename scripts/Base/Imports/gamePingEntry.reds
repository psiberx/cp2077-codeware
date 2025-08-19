public native struct gamePingEntry {
  public native let owner: wref<GameObject>;
  public native let worldPosition: Vector4;
  public native let time: netTime;
  public native let pingType: gamedataPingType;
  public native let hitObject: wref<Entity>;
}
