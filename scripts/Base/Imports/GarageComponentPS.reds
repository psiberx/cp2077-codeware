public importonly class GarageComponentPS extends GameComponentPS {
  public native persistent let spawnedVehiclesData: array<vehicleGarageComponentVehicleData>;
  public native persistent let unregisteredVehiclesData: array<vehicleGarageComponentVehicleData>;
  public native persistent let unlockedVehicles: array<GarageVehicleID>;
  public native persistent let unlockedVehicleArray: array<vehicleUnlockedVehicle>;
  public native persistent let uiFavoritedVehicles: array<GarageVehicleID>;
  public native persistent let activeVehicles: [GarageVehicleID; 3];
  public native persistent let mountedVehicleData: vehicleGarageComponentVehicleData;
  public native persistent let mountedVehicleStolen: Bool;
}
