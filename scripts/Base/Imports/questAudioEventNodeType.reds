public native class questAudioEventNodeType extends questIAudioNodeType {
  public native let events: array<audioAudEventStruct>;
  public native let musicEvents: array<audioAudEventStruct>;
  public native let switches: array<audioAudSwitch>;
  public native let params: array<audioAudParameter>;
  public native let dynamicParams: array<CName>;
  public native let event: audioAudEventStruct;
  public native let ambientUniqueName: CName;
  public native let emitter: CName;
  public native let isMusic: Bool;
  public native let objectRef: EntityReference;
  public native let isPlayer: Bool;
}
