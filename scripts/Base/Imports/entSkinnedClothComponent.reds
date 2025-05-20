public importonly class entSkinnedClothComponent extends entISkinTargetComponent {
  native let graphicsMesh: ResourceAsyncRef; // raRef<CMesh>
  native let physicalMesh: ResourceAsyncRef; // raRef<CMesh>
  native let isEnabled: Bool;
  native let LODMode: entMeshComponentLODMode;
  native let meshAppearance: CName;
  native let chunkMask: Uint64;
  native let compiledTopologyData: meshCookedClothMeshTopologyData;
}
