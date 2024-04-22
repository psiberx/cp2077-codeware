public native class scnVoicesetComponentPS extends GameComponentPS {
  native persistent let blockedInputs: array<entVoicesetInputToBlock>;
  native persistent let voiceTag: CName;
  native persistent let NPCHighLevelState: gamedataNPCHighLevelState;
  native persistent let gruntSetIndex: Uint32;
  native persistent let areVoicesetLinesEnabled: Bool;
  native persistent let areVoicesetGruntsEnabled: Bool;
}
