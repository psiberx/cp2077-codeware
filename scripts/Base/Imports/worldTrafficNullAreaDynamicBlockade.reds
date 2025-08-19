public native struct worldTrafficNullAreaDynamicBlockade {
  public native let areaID: Uint64;
  public native let offmeshLinks: array<Uint64>;
  public native let affectedTrafficLanes: array<worldTrafficLaneUID>;
  public native let permanentlyEnabledByDefault: Bool;
}
