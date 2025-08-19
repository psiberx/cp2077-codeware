public native struct gameMuppetSubStepData {
  public native let frameId: Uint32;
  public native let parentFrameId: Uint32;
  public native let parentFramePrimaryColor: Bool;
  public native let inputState: gameMuppetInputState;
  public native let state: gameMuppetState;
  public native let resimulationSubsteps: array<gameMuppetSubStepData>;
}
