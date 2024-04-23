public native struct worldOffMeshConnectionsData {
  native let verts: array<Float>;
  native let radii: array<Float>;
  native let flags: array<Uint16>;
  native let areas: array<Uint8>;
  native let directions: array<Uint8>;
  native let ids: array<Uint64>;
  native let tagIntervals: array<Uint16>;
  native let tagsX: array<CName>;
  native let globalNodeIDs: array<GlobalNodeID>;
  native let userData: array<ref<worldOffMeshUserData>>;
}
