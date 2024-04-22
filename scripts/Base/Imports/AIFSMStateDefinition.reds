public native struct AIFSMStateDefinition {
  native let onUpdateTransition: AIFSMTransitionListDefinition;
  native let onCompleteTransition: AIFSMTransitionListDefinition;
  native let onSuccessTransition: AIFSMTransitionListDefinition;
  native let onFailureTransition: AIFSMTransitionListDefinition;
  native let onInterruptionTransition: AIFSMTransitionListDefinition;
  native let onEventTransitions: AIFSMTransitionListDefinition;
}
