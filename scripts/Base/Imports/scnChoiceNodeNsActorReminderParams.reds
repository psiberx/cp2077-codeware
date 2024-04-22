public native class scnChoiceNodeNsActorReminderParams extends ISerializable {
  native let useCustomReminder: Bool;
  native let reminderActor: scnActorId;
  native let waitTimeForReminderA: scnSceneTime;
  native let waitTimeForReminderB: scnSceneTime;
  native let waitTimeForReminderC: scnSceneTime;
  native let waitTimeForLooping: scnSceneTime;
  native let cutReminderEnabled: Bool;
  native let waitTimeToCutReminder: Float;
}
