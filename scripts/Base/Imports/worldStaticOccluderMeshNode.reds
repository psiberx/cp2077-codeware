public native class worldStaticOccluderMeshNode extends worldNode {
  public native let occluderType: visWorldOccluderType;
  public native let color: Color;
  public native let autohideDistanceScale: Uint8;
  public native let mesh: ResourceAsyncRef; // raRef<CMesh>
}
