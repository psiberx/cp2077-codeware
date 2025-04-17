public importonly native class GarageComponentPS extends GameComponentPS {
  native persistent let spawnedVehiclesData: array<vehicleGarageComponentVehicleData>;
  native persistent let unlockedVehicles: array<GarageVehicleID>;
  native persistent let unlockedVehicleArray: array<vehicleUnlockedVehicle>;
  native persistent let uiFavoritedVehicles: array<GarageVehicleID>;
  native persistent let activeVehicles: [GarageVehicleID; 3];
  native persistent let mountedVehicleData: vehicleGarageComponentVehicleData;
  native persistent let mountedVehicleStolen: Bool;
}
