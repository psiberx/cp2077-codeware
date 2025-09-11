public native class scnChoiceNode extends scnSceneGraphNode {
  public native let displayNameOverride: String;
  public native let localizedDisplayNameOverride: LocalizationString;
  public native let options: array<scnChoiceNodeOption>;
  public native let mode: scnChoiceNodeNsOperationMode;
  public native let persistentLineEvents: array<scnSceneEventId>;
  public native let customPersistentLine: scnscreenplayItemId;
  public native let timedParams: ref<scnChoiceNodeNsTimedParams>;
  public native let reminderParams: ref<scnChoiceNodeNsActorReminderParams>;
  public native let shapeParams: ref<scnInteractionShapeParams>;
  public native let lookAtParams: ref<scnChoiceNodeNsLookAtParams>;
  public native let forceAttachToScreenCondition: ref<questIBaseCondition>;
  public native let choiceGroup: CName;
  public native let cpoHoldInputActionSection: Bool;
  public native let doNotTurnOffPreventionSystem: Bool;
  public native let ataParams: scnChoiceNodeNsAttachToActorParams;
  public native let atpParams: scnChoiceNodeNsAttachToPropParams;
  public native let atgoParams: scnChoiceNodeNsAttachToGameObjectParams;
  public native let atsParams: scnChoiceNodeNsAttachToScreenParams;
  public native let atwParams: scnChoiceNodeNsAttachToWorldParams;
  public native let choicePriority: Uint8;
  public native let hubPriority: Uint8;
  public native let mappinParams: ref<scnChoiceNodeNsMappinParams>;
  public native let interruptCapability: scnInterruptCapability;
  public native let interruptionSpeakerOverride: scnActorId;
  public native let choiceFlags: Uint16; // scnChoiceNodeNsChoiceNodeBitFlags
  public native let alwaysUseBrainGender: Bool;
  public native let timedSectionCondition: ref<scnTimedCondition>;
  public native let reminderCondition: ref<scnReminderCondition>;
}
