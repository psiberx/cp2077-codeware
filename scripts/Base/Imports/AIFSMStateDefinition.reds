public native struct AIFSMStateDefinition {
  public native let onUpdateTransition: AIFSMTransitionListDefinition;
  public native let onCompleteTransition: AIFSMTransitionListDefinition;
  public native let onSuccessTransition: AIFSMTransitionListDefinition;
  public native let onFailureTransition: AIFSMTransitionListDefinition;
  public native let onInterruptionTransition: AIFSMTransitionListDefinition;
  public native let onEventTransitions: AIFSMTransitionListDefinition;
  public native let childNode: ref<AICTreeNodeDefinition>;
}
