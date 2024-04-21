public native class worldFoliageNode extends worldNode {
  native let mesh: ResourceAsyncRef; // raRef<CMesh>
  native let meshAppearance: CName;
  native let foliageResource: ResourceAsyncRef; // raRef<worldFoliageCompiledResource>
  native let foliageLocalBounds: Box;
  native let autoHideDistanceScale: Float;
  native let lodDistanceScale: Float;
  native let streamingDistance: Float;
  native let populationSpanInfo: worldFoliagePopulationSpanInfo;
  native let destructionHash: Uint64;
  native let meshHeight: Float;
}
