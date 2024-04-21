public native struct worldCompiledEffectInfo {
  native let placementTags: array<CName>;
  native let componentNames: array<CName>;
  native let relativePositions: array<Vector3>;
  native let relativeRotations: array<Quaternion>;
  native let placementInfos: array<worldCompiledEffectPlacementInfo>;
  native let eventsSortedByRUID: array<worldCompiledEffectEventInfo>;
}
