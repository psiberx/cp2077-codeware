public native class entSoundEvent extends Event {
  native let eventName: CName;
  native let switches: array<audioAudSwitch>;
  native let params: array<audioAudParameter>;
  native let dynamicParams: array<CName>;
}
