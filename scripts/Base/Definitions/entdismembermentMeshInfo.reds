public native struct entdismembermentMeshInfo {
  native let Mesh: ResourceAsyncRef; // raRef<CMesh>
  native let MeshAppearance: CName;
  native let AppearanceMap: array<entdismembermentAppearanceMatch>;
  native let ShouldReceiveDecal: Bool;
  native let Offset: Transform;
  native let Scale: Vector3;
  native let Physics: entdismembermentPhysicsInfo;
}
