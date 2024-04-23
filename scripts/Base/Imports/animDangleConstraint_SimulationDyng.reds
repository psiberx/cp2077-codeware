public native class animDangleConstraint_SimulationDyng extends animDangleConstraint_Simulation {
  native let HACK_checkDangleTeleport: Bool;
  native let substepTime: Float;
  native let solverIterations: Uint32;
  native let particlesContainer: animDyngParticlesContainer;
  native let dyngConstraint: ref<animIDyngConstraint>;
}
