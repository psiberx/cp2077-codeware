public native class questEquipItemParams extends AICommandParams {
  public native let slotId: TweakDBID;
  public native let type: questNodeType;
  public native let itemId: TweakDBID;
  public native let equipDurationOverride: Float;
  public native let unequipDurationOverride: Float;
  public native let failIfItemNotFound: Bool;
  public native let instant: Bool;
  public native let equipLastWeapon: Bool;
  public native let forceFirstEquip: Bool;
  public native let ignoreStateMachine: Bool;
  public native let isPlayer: Bool;
  public native let equipTypes: gameItemEquipContexts;
  public native let unequipTypes: gameItemUnequipContexts;
  public native let byItem: Bool;
}
