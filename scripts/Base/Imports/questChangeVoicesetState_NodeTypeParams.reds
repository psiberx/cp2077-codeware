public native struct questChangeVoicesetState_NodeTypeParams {
  public native let puppetRef: EntityReference;
  public native let isPlayer: Bool;
  public native let enableVoicesetLines: Bool;
  public native let enableVoicesetGrunts: Bool;
  public native let inputsToBlock: array<entVoicesetInputToBlock>;
}
