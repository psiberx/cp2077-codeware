public native struct entdismembermentMeshInfo {
  public native let Mesh: ResourceAsyncRef; // raRef<CMesh>
  public native let MeshAppearance: CName;
  public native let AppearanceMap: array<entdismembermentAppearanceMatch>;
  public native let ShouldReceiveDecal: Bool;
  public native let Offset: Transform;
  public native let Scale: Vector3;
  public native let Physics: entdismembermentPhysicsInfo;
}
