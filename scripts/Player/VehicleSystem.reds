@addMethod(VehicleSystem)
public native func ToggleGarageVehicle(garageID: GarageVehicleID, enable: Bool) -> Bool

@addMethod(VehicleSystem)
public func EnablePlayerVehicleID(vehicleID: TweakDBID, enable: Bool, opt despawnIfDisabling: Bool) -> Bool {
    let playerVehicles = TweakDBInterface.GetForeignKeyArray(t"Vehicle.vehicle_list.list");

    if !ArrayContains(playerVehicles, vehicleID) {
        return false;
    }

    let garageID: GarageVehicleID;
    garageID.recordID = vehicleID;

    let success = this.ToggleGarageVehicle(garageID, enable);

    if success && !enable && despawnIfDisabling {
        this.DespawnPlayerVehicle(garageID);
    }

    return success;
}
