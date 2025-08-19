public native struct interopTerrainSystemInstanceInfo {
  public native let cellSize: Uint32;
  public native let cellRes: Uint32;
  public native let numUsedCells: Uint32;
  public native let numPatches: Uint32;
  public native let numPatchesFromTerrainNodes: Uint32;
  public native let numPatchesFromRoadNodes: Uint32;
  public native let isEnabled: Bool;
  public native let isVisibleCompiled: Bool;
  public native let useDebugDraw: Bool;
  public native let gridWidth: Uint32;
  public native let gridHeight: Uint32;
  public native let numUsedLODCells: array<Uint32>;
}
