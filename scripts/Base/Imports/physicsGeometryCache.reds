public native class physicsGeometryCache extends CResource {
  native let sectorEntries: array<physicsSectorEntry>;
  native let sectorGeometries: array<physicsGeometryKey>;
  native let sectorCacheEntries: array<physicsSectorCacheEntry>;
  native let alwaysLoadedSector: physicsSectorEntry;
}
