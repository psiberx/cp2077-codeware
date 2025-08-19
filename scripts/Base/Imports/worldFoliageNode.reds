public native class worldFoliageNode extends worldNode {
  public native let mesh: ResourceAsyncRef; // raRef<CMesh>
  public native let meshAppearance: CName;
  public native let foliageResource: ResourceAsyncRef; // raRef<worldFoliageCompiledResource>
  public native let foliageLocalBounds: Box;
  public native let autoHideDistanceScale: Float;
  public native let lodDistanceScale: Float;
  public native let streamingDistance: Float;
  public native let populationSpanInfo: worldFoliagePopulationSpanInfo;
  public native let destructionHash: Uint64;
  public native let meshHeight: Float;
}
