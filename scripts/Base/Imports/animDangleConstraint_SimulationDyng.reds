public native class animDangleConstraint_SimulationDyng extends animDangleConstraint_Simulation {
  public native let HACK_checkDangleTeleport: Bool;
  public native let substepTime: Float;
  public native let solverIterations: Uint32;
  public native let particlesContainer: animDyngParticlesContainer;
  public native let dyngConstraint: ref<animIDyngConstraint>;
}
