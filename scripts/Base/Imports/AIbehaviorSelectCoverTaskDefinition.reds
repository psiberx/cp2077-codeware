public native class AIbehaviorSelectCoverTaskDefinition extends AIbehaviorTaskDefinition {
  native let cover: ref<AIArgumentMapping>;
  native let coverID: ref<AIArgumentMapping>;
  native let multiCoverID: ref<AIArgumentMapping>;
  native let combatTarget: ref<AIArgumentMapping>;
  native let friendlyTarget: ref<AIArgumentMapping>;
  native let combatZone: ref<AIArgumentMapping>;
  native let sectorSelection: CName;
  native let ignoreRestrictMovementArea: ref<AIArgumentMapping>;
  native let selectionPreset: ref<AIArgumentMapping>;
  native let onActivationSelectionPreset: ref<AIArgumentMapping>;
  native let secondStagePreset: ref<AIArgumentMapping>;
  native let coverChangeThreshold: ref<AIArgumentMapping>;
  native let coverGatheringCenterObject: ref<AIArgumentMapping>;
  native let coverDisablingDuration: ref<AIArgumentMapping>;
}
