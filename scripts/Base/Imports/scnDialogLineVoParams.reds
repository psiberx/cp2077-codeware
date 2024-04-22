public native struct scnDialogLineVoParams {
  native let voContext: locVoiceoverContext;
  native let voExpression: locVoiceoverExpression;
  native let customVoEvent: CName;
  native let disableHeadMovement: Bool;
  native let isHolocallSpeaker: Bool;
  native let ignoreSpeakerIncapacitation: Bool;
  native let alwaysUseBrainGender: Bool;
}
