public native struct worldNavigationTileData {
  public native let tileX: Int32;
  public native let tileY: Int32;
  public native let tileIndex: Uint32;
  public native let bufferIndex: Uint32;
  public native let agentSize: NavGenAgentSize;
  public native let offMeshConnections: worldOffMeshConnectionsData;
  public native let tileRef: Uint64;
  public native let activeVariantIDs: array<Uint32>;
  public native let allVariantIDs: array<Uint32>;
}
