public native class VehicleSlotsState extends ISerializable {
  native persistent let vehicleDoorState: VehicleDoorState;
  native persistent let vehicleWindowState: EVehicleWindowState;
  native persistent let vehicleInteractionState: VehicleDoorInteractionState;
}
