public native struct SParticleEmitterLODLevel {
  public native let emitterDurationSettings: EmitterDurationSettings;
  public native let emitterDelaySettings: EmitterDelaySettings;
  public native let burstList: array<ParticleBurst>;
  public native let birthRate: ref<IEvaluatorFloat>;
  public native let sortingMode: rendEParticleSortingMode;
  public native let lodSwitchDistance: Float;
  public native let isEnabled: Bool;
}
