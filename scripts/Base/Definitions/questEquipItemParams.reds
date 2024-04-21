public native class questEquipItemParams extends AICommandParams {
  native let slotId: TweakDBID;
  native let type: questNodeType;
  native let itemId: TweakDBID;
  native let equipDurationOverride: Float;
  native let unequipDurationOverride: Float;
  native let failIfItemNotFound: Bool;
  native let instant: Bool;
  native let equipLastWeapon: Bool;
  native let forceFirstEquip: Bool;
  native let ignoreStateMachine: Bool;
  native let isPlayer: Bool;
  native let equipTypes: gameItemEquipContexts;
  native let unequipTypes: gameItemUnequipContexts;
  native let byItem: Bool;
}
