public native class AIbehaviorSelectCoverTaskDefinition extends AIbehaviorTaskDefinition {
  public native let cover: ref<AIArgumentMapping>;
  public native let coverID: ref<AIArgumentMapping>;
  public native let multiCoverID: ref<AIArgumentMapping>;
  public native let combatTarget: ref<AIArgumentMapping>;
  public native let friendlyTarget: ref<AIArgumentMapping>;
  public native let combatZone: ref<AIArgumentMapping>;
  public native let sectorSelection: CName;
  public native let ignoreRestrictMovementArea: ref<AIArgumentMapping>;
  public native let selectionPreset: ref<AIArgumentMapping>;
  public native let onActivationSelectionPreset: ref<AIArgumentMapping>;
  public native let secondStagePreset: ref<AIArgumentMapping>;
  public native let coverChangeThreshold: ref<AIArgumentMapping>;
  public native let coverGatheringCenterObject: ref<AIArgumentMapping>;
  public native let coverDisablingDuration: ref<AIArgumentMapping>;
}
