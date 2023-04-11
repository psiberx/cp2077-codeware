public native struct meshCookedClothMeshTopologyData {
  native let gfxIndexToTriangles: array<Uint32>;
  native let phxIndexToTriangles: array<Uint32>;
  native let gfxBarycentrics: array<Uint32>;
  native let phxBarycentrics: array<Uint32>;
  native let phxLodSwitchData: array<Uint32>;
  native let phxSimulated: array<Uint32>;
  native let gfxNumIndicesToTriangles: Uint32;
  native let phxNumIndicesToTriangles: Uint32;
  native let gfxNumBarycentrics: Uint32;
  native let phxNumBarycentrics: Uint32;
  native let phxNumLodSwitchData: Uint32;
  native let phxNumSimulated: Uint32;
}
