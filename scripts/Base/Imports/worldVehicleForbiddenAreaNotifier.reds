public native class worldVehicleForbiddenAreaNotifier extends worldITriggerAreaNotifer {
  native let innerAreaBoundToOuterArea: Bool;
  native let parkingSpots: array<NodeRef>;
  native let innerAreaSpeedLimit: Float;
  native let areaSpeedLimit: Float;
  native let enableNullArea: Bool;
  native let dismount: Bool;
  native let enableSummoning: Bool;
}
