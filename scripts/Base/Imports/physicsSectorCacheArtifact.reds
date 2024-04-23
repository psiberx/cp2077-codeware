public native class physicsSectorCacheArtifact extends CResource {
  native let sectorGeometryKeys: array<physicsGeometryKey>;
  native let sectorInPlaceGeometry: ref<physicsGeometryCacheArtifact>;
  native let sectorBounds: Box;
}
