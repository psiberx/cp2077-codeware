public native class scnVoicesetComponentPS extends GameComponentPS {
  public native persistent let blockedInputs: array<entVoicesetInputToBlock>;
  public native persistent let voiceTag: CName;
  public native persistent let NPCHighLevelState: gamedataNPCHighLevelState;
  public native persistent let gruntSetIndex: Uint32;
  public native persistent let areVoicesetLinesEnabled: Bool;
  public native persistent let areVoicesetGruntsEnabled: Bool;
}
