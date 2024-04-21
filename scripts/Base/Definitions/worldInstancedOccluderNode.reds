public native class worldInstancedOccluderNode extends worldNode {
  native let worldBounds: Box;
  native let occluderType: visWorldOccluderType;
  native let autohideDistanceScale: Uint8;
  native let mesh: ResourceAsyncRef; // raRef<CMesh>
}
