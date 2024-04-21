public native struct rendEmitterLOD {
  native let lodSwitchDistance: Float;
  native let burstList: array<rendParticleBurst>;
  native let birthRate: array<Float>;
  native let emitterDurationSettings: rendEmitterDurationSettings;
  native let emitterDelaySettings: rendEmitterDelaySettings;
  native let sortingMode: rendEParticleSortingMode;
  native let isEnabled: Bool;
}
