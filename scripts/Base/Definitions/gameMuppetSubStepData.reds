public native struct gameMuppetSubStepData {
  native let frameId: Uint32;
  native let parentFrameId: Uint32;
  native let parentFramePrimaryColor: Bool;
  native let inputState: gameMuppetInputState;
  native let state: gameMuppetState;
  native let resimulationSubsteps: array<gameMuppetSubStepData>;
}
