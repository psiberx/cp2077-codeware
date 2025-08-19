public native class entStaticOccluderMeshComponent extends IPlacedComponent {
  public native let mesh: ResourceRef; // rRef<CMesh>
  public native let scale: Vector3;
  public native let color: Color;
  public native let occluderType: visWorldOccluderType;
  public native let occluderAutohideDistanceScale: Uint8;
}
