public native struct rendEmitterLOD {
  public native let lodSwitchDistance: Float;
  public native let burstList: array<rendParticleBurst>;
  public native let birthRate: array<Float>;
  public native let emitterDurationSettings: rendEmitterDurationSettings;
  public native let emitterDelaySettings: rendEmitterDelaySettings;
  public native let sortingMode: rendEParticleSortingMode;
  public native let isEnabled: Bool;
}
