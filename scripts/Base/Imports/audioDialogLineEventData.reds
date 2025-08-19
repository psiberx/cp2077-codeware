public native struct audioDialogLineEventData {
  public native let stringId: CRUID;
  public native let context: locVoiceoverContext;
  public native let expression: locVoiceoverExpression;
  public native let isPlayer: Bool;
  public native let isRewind: Bool;
  public native let isHolocall: Bool;
  public native let customVoEvent: CName;
  public native let seekTime: Float;
  public native let playbackSpeedParameter: Float;
}
