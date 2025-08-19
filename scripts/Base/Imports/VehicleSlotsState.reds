@neverRef()
public native class VehicleSlotsState extends ISerializable {
  public native persistent let vehicleDoorState: VehicleDoorState;
  public native persistent let vehicleWindowState: EVehicleWindowState;
  public native persistent let vehicleInteractionState: VehicleDoorInteractionState;
}
