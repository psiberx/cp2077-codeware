public native class worldVehicleForbiddenAreaNotifier extends worldITriggerAreaNotifer {
  public native let innerAreaBoundToOuterArea: Bool;
  public native let innerAreaOutline: ref<AreaShapeOutline>;
  public native let parkingSpots: array<NodeRef>;
  public native let innerAreaSpeedLimit: Float;
  public native let areaSpeedLimit: Float;
  public native let enableNullArea: Bool;
  public native let dismount: Bool;
  public native let enableSummoning: Bool;
}
