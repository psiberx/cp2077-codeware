public native class entStaticOccluderMeshComponent extends IPlacedComponent {
  native let mesh: ResourceRef; // rRef<CMesh>
  native let scale: Vector3;
  native let color: Color;
  native let occluderType: visWorldOccluderType;
  native let occluderAutohideDistanceScale: Uint8;
}
