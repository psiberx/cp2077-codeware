public native class physicsGeometryCache extends CResource {
  public native let sectorEntries: array<physicsSectorEntry>;
  public native let sectorGeometries: array<physicsGeometryKey>;
  public native let sectorCacheEntries: array<physicsSectorCacheEntry>;
  public native let alwaysLoadedSector: physicsSectorEntry;
}
