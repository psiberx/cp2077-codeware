public native struct entdismembermentFillMeshInfo {
  public native let Mesh: ResourceAsyncRef; // raRef<CMesh>
  public native let MeshAppearance: CName;
  public native let AppearanceMap: array<entdismembermentAppearanceMatch>;
  public native let ShouldReceiveDecal: Bool;
  public native let BodyPartMask: Uint32; // physicsRagdollBodyPartE
  public native let WoundType: Uint16; // entdismembermentWoundTypeE
  public native let CullMesh: Uint16; // entdismembermentWoundTypeE
  public native let Offset: Transform;
  public native let Scale: Vector3;
  public native let Physics: entdismembermentPhysicsInfo;
  public native let Placement: Uint16; // entdismembermentPlacementE
  public native let Simulation: entdismembermentSimulationTypeE;
  public native let Dangle: entdismembermentDangleInfo;
}
