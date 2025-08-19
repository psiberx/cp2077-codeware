public native struct worldCompiledEffectInfo {
  public native let placementTags: array<CName>;
  public native let componentNames: array<CName>;
  public native let relativePositions: array<Vector3>;
  public native let relativeRotations: array<Quaternion>;
  public native let placementInfos: array<worldCompiledEffectPlacementInfo>;
  public native let eventsSortedByRUID: array<worldCompiledEffectEventInfo>;
}
