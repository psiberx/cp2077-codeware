public native struct SParticleEmitterLODLevel {
  native let emitterDurationSettings: EmitterDurationSettings;
  native let emitterDelaySettings: EmitterDelaySettings;
  native let burstList: array<ParticleBurst>;
  native let birthRate: ref<IEvaluatorFloat>;
  native let sortingMode: rendEParticleSortingMode;
  native let lodSwitchDistance: Float;
  native let isEnabled: Bool;
}
