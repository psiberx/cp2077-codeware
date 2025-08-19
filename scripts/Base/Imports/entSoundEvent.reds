public native class entSoundEvent extends Event {
  public native let eventName: CName;
  public native let switches: array<audioAudSwitch>;
  public native let params: array<audioAudParameter>;
  public native let dynamicParams: array<CName>;
}
