public native class AICTreeNodeFSMDefinition extends AICTreeNodeCompositeDefinition {
  public native let defaultState: Uint16;
  public native let transitions: array<AIFSMTransitionDefinition>;
  public native let onEventTransitions: array<AIFSMEventTransitionsListDefinition>;
  public native let states: array<AIFSMStateDefinition>;
  public native let sharedVars: AISharedVarTableDefinition;
}
