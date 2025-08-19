public native class questCharacterMount_ConditionType extends questICharacterConditionType {
  public native let anyParent: Bool;
  public native let parentRef: EntityReference;
  public native let parentIsPlayer: Bool;
  public native let anyChild: Bool;
  public native let childRef: EntityReference;
  public native let childIsPlayer: Bool;
  public native let condition: questMountConditionType;
  public native let enterAnimationFinished: Bool;
  public native let role: gameMountingSlotRole;
  public native let usePlayersVehicle: Bool;
  public native let playerVehicleName: String;
  public native let vehicleType: questMountVehicleType;
  public native let vehicleOrigin: questMountVehicleOrigin;
  public native let vehicleAfiliation: gamedataAffiliation;
}
