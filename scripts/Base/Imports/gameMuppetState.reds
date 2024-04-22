public native struct gameMuppetState {
  native let frameId: Uint32;
  native let highLevelState: gameMuppetHighLevelState;
  native let healthState: gameMuppetHealthState;
  native let physicalMoveState: gameMuppetPhysicalState;
  native let lookState: gameMuppetLookState;
  native let moveState: gameMuppetMoveState;
  native let upperBodyState: gameMuppetUpperBodyState;
  native let scanningState: gameMuppetScanningState;
  native let inventoryState: gameMuppetInventoryState;
  native let abilities: gameMuppetAbilities;
  native let stateMachinesSnapshot: gameMuppetStateMachinesSnapshot;
  native let controllersSnapshot: gameMuppetControllersSnapshot;
  native let snapFrameId: Uint32;
}
