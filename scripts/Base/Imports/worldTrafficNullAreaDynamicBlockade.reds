public native struct worldTrafficNullAreaDynamicBlockade {
  native let areaID: Uint64;
  native let offmeshLinks: array<Uint64>;
  native let affectedTrafficLanes: array<worldTrafficLaneUID>;
  native let permanentlyEnabledByDefault: Bool;
}
