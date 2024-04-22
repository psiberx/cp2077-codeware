public native struct worldNavigationTileData {
  native let tileX: Int32;
  native let tileY: Int32;
  native let tileIndex: Uint32;
  native let bufferIndex: Uint32;
  native let agentSize: NavGenAgentSize;
  native let offMeshConnections: worldOffMeshConnectionsData;
  native let tileRef: Uint64;
  native let activeVariantIDs: array<Uint32>;
  native let allVariantIDs: array<Uint32>;
}
