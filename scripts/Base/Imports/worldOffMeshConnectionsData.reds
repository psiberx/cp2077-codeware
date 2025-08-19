public native struct worldOffMeshConnectionsData {
  public native let verts: array<Float>;
  public native let radii: array<Float>;
  public native let flags: array<Uint16>;
  public native let areas: array<Uint8>;
  public native let directions: array<Uint8>;
  public native let ids: array<Uint64>;
  public native let tagIntervals: array<Uint16>;
  public native let tagsX: array<CName>;
  public native let globalNodeIDs: array<GlobalNodeID>;
  public native let userData: array<ref<worldOffMeshUserData>>;
}
