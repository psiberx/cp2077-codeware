public native class physicsSectorCacheArtifact extends CResource {
  public native let sectorGeometryKeys: array<physicsGeometryKey>;
  public native let sectorInPlaceGeometry: ref<physicsGeometryCacheArtifact>;
  public native let sectorBounds: Box;
}
