public importonly native class entSkinnedClothComponent extends entISkinTargetComponent {
  native let graphicsMesh: ResourceAsyncRef;
  native let physicalMesh: ResourceAsyncRef;
  native let isEnabled: Bool;
  native let LODMode: entMeshComponentLODMode;
  native let meshAppearance: CName;
  native let chunkMask: Uint64;
  native let compiledTopologyData: meshCookedClothMeshTopologyData;
}
