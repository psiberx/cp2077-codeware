public native class scnReminderCondition extends ISerializable {
  native let useCustomReminder: Bool;
  native let reminderActor: scnActorId;
  native let waitTimeForReminderA: scnSceneTime;
  native let waitTimeForReminderB: scnSceneTime;
  native let waitTimeForReminderC: scnSceneTime;
  native let waitTimeForLooping: scnSceneTime;
  native let startTime: scnSceneTime;
  native let processStep: scnReminderConditionProcessStep;
  native let playing: Bool;
  native let running: Bool;
  native let reminderParams: scnChoiceNodeNsReminderParams;
}
