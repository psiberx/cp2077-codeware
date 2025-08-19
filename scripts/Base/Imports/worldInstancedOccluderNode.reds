public native class worldInstancedOccluderNode extends worldNode {
  public native let worldBounds: Box;
  public native let occluderType: visWorldOccluderType;
  public native let autohideDistanceScale: Uint8;
  public native let mesh: ResourceAsyncRef; // raRef<CMesh>
}
