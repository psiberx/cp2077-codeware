public native struct audioDialogLineEventData {
  native let stringId: CRUID;
  native let context: locVoiceoverContext;
  native let expression: locVoiceoverExpression;
  native let isPlayer: Bool;
  native let isRewind: Bool;
  native let isHolocall: Bool;
  native let customVoEvent: CName;
  native let seekTime: Float;
  native let playbackSpeedParameter: Float;
}
