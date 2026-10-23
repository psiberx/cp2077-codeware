// Game 2.5: worldInstancedMeshNode is a cooked node (parent worldCookedNode, size 0x98/0xB8 editor) with only
// cookedWorldTransformsBuffer and version (REDmod metadata.json; 2.5 exe class registration 0x1322F7A).
// The 2.31 fields (mesh, meshAppearance, ..., instanceBatches, boundingBoxes, streamingDistances) are gone.
public native class worldInstancedMeshNode extends worldCookedNode {
  public native let version: Uint8;
}
