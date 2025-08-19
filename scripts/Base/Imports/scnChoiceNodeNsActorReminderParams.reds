public native class scnChoiceNodeNsActorReminderParams extends ISerializable {
  public native let useCustomReminder: Bool;
  public native let reminderActor: scnActorId;
  public native let waitTimeForReminderA: scnSceneTime;
  public native let waitTimeForReminderB: scnSceneTime;
  public native let waitTimeForReminderC: scnSceneTime;
  public native let waitTimeForLooping: scnSceneTime;
  public native let cutReminderEnabled: Bool;
  public native let waitTimeToCutReminder: Float;
}
