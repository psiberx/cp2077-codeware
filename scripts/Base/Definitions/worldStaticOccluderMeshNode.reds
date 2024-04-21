public native class worldStaticOccluderMeshNode extends worldNode {
  native let occluderType: visWorldOccluderType;
  native let color: Color;
  native let autohideDistanceScale: Uint8;
  native let mesh: ResourceAsyncRef; // raRef<CMesh>
}
