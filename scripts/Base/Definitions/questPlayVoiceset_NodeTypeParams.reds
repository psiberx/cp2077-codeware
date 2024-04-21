public native struct questPlayVoiceset_NodeTypeParams {
  native let puppetRef: EntityReference;
  native let isPlayer: Bool;
  native let voicesetName: CName;
  native let useVoicesetSystem: Bool;
  native let playOnlyGrunt: Bool;
  native let overridingVoiceoverContext: locVoiceoverContext;
  native let overrideVoiceoverExpression: Bool;
  native let overridingVoiceoverExpression: locVoiceoverExpression;
  native let overrideVisualStyle: Bool;
  native let overridingVisualStyle: scnDialogLineVisualStyle;
}
