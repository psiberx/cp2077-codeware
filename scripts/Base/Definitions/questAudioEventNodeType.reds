public native class questAudioEventNodeType extends questIAudioNodeType {
  native let events: array<audioAudEventStruct>;
  native let musicEvents: array<audioAudEventStruct>;
  native let switches: array<audioAudSwitch>;
  native let params: array<audioAudParameter>;
  native let dynamicParams: array<CName>;
  native let event: audioAudEventStruct;
  native let ambientUniqueName: CName;
  native let emitter: CName;
  native let isMusic: Bool;
  native let objectRef: EntityReference;
  native let isPlayer: Bool;
}
