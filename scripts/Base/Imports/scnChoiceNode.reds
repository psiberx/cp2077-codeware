public native class scnChoiceNode extends scnSceneGraphNode {
  native let displayNameOverride: String;
  native let localizedDisplayNameOverride: LocalizationString;
  native let options: array<scnChoiceNodeOption>;
  native let mode: scnChoiceNodeNsOperationMode;
  native let persistentLineEvents: array<scnSceneEventId>;
  native let customPersistentLine: scnscreenplayItemId;
  native let choiceGroup: CName;
  native let cpoHoldInputActionSection: Bool;
  native let doNotTurnOffPreventionSystem: Bool;
  native let ataParams: scnChoiceNodeNsAttachToActorParams;
  native let atpParams: scnChoiceNodeNsAttachToPropParams;
  native let atgoParams: scnChoiceNodeNsAttachToGameObjectParams;
  native let atsParams: scnChoiceNodeNsAttachToScreenParams;
  native let atwParams: scnChoiceNodeNsAttachToWorldParams;
  native let choicePriority: Uint8;
  native let hubPriority: Uint8;
  native let interruptCapability: scnInterruptCapability;
  native let interruptionSpeakerOverride: scnActorId;
  native let alwaysUseBrainGender: Bool;
}
