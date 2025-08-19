public native struct gameMuppetState {
  public native let frameId: Uint32;
  public native let highLevelState: gameMuppetHighLevelState;
  public native let healthState: gameMuppetHealthState;
  public native let physicalMoveState: gameMuppetPhysicalState;
  public native let lookState: gameMuppetLookState;
  public native let moveState: gameMuppetMoveState;
  public native let upperBodyState: gameMuppetUpperBodyState;
  public native let scanningState: gameMuppetScanningState;
  public native let inventoryState: gameMuppetInventoryState;
  public native let abilities: gameMuppetAbilities;
  public native let stateMachinesSnapshot: gameMuppetStateMachinesSnapshot;
  public native let controllersSnapshot: gameMuppetControllersSnapshot;
  public native let snapFrameId: Uint32;
}
