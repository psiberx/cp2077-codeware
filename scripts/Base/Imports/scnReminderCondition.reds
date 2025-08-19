public native class scnReminderCondition extends ISerializable {
  public native let useCustomReminder: Bool;
  public native let reminderActor: scnActorId;
  public native let waitTimeForReminderA: scnSceneTime;
  public native let waitTimeForReminderB: scnSceneTime;
  public native let waitTimeForReminderC: scnSceneTime;
  public native let waitTimeForLooping: scnSceneTime;
  public native let startTime: scnSceneTime;
  public native let processStep: scnReminderConditionProcessStep;
  public native let playing: Bool;
  public native let running: Bool;
  public native let reminderParams: scnChoiceNodeNsReminderParams;
}
