public native struct questChangeVoicesetState_NodeTypeParams {
  native let puppetRef: EntityReference;
  native let isPlayer: Bool;
  native let enableVoicesetLines: Bool;
  native let enableVoicesetGrunts: Bool;
  native let inputsToBlock: array<entVoicesetInputToBlock>;
}
