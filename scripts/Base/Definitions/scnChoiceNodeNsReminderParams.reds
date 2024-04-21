public native struct scnChoiceNodeNsReminderParams {
  native let reminderEnabled: Bool;
  native let useCustomReminder: Bool;
  native let reminderActor: scnActorId;
  native let waitTimeForReminderA: scnSceneTime;
  native let waitTimeForReminderB: scnSceneTime;
  native let waitTimeForReminderC: scnSceneTime;
  native let waitTimeForLooping: scnSceneTime;
}
