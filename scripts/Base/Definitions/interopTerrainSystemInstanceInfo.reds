public native struct interopTerrainSystemInstanceInfo {
  native let cellSize: Uint32;
  native let cellRes: Uint32;
  native let numUsedCells: Uint32;
  native let numPatches: Uint32;
  native let numPatchesFromTerrainNodes: Uint32;
  native let numPatchesFromRoadNodes: Uint32;
  native let isEnabled: Bool;
  native let isVisibleCompiled: Bool;
  native let useDebugDraw: Bool;
  native let gridWidth: Uint32;
  native let gridHeight: Uint32;
  native let numUsedLODCells: array<Uint32>;
}
