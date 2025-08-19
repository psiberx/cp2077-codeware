public importonly class entSkinnedClothComponent extends entISkinTargetComponent {
  public native let graphicsMesh: ResourceAsyncRef; // raRef<CMesh>
  public native let physicalMesh: ResourceAsyncRef; // raRef<CMesh>
  public native let isEnabled: Bool;
  public native let LODMode: entMeshComponentLODMode;
  public native let meshAppearance: CName;
  public native let chunkMask: Uint64;
  public native let compiledTopologyData: meshCookedClothMeshTopologyData;
}
