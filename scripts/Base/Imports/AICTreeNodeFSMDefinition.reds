public native class AICTreeNodeFSMDefinition extends AICTreeNodeCompositeDefinition {
  native let defaultState: Uint16;
  native let transitions: array<AIFSMTransitionDefinition>;
  native let onEventTransitions: array<AIFSMEventTransitionsListDefinition>;
  native let states: array<AIFSMStateDefinition>;
  native let sharedVars: AISharedVarTableDefinition;
}
