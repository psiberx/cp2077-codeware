public native class questCharacterMount_ConditionType extends questICharacterConditionType {
  native let anyParent: Bool;
  native let parentRef: EntityReference;
  native let parentIsPlayer: Bool;
  native let anyChild: Bool;
  native let childRef: EntityReference;
  native let childIsPlayer: Bool;
  native let condition: questMountConditionType;
  native let enterAnimationFinished: Bool;
  native let role: gameMountingSlotRole;
  native let usePlayersVehicle: Bool;
  native let playerVehicleName: String;
  native let vehicleType: questMountVehicleType;
  native let vehicleOrigin: questMountVehicleOrigin;
  native let vehicleAfiliation: gamedataAffiliation;
}
