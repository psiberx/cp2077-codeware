public native class questTriggerCondition extends questCondition {
  native let type: questTriggerConditionType;
  native let triggerAreaRef: NodeRef;
  native let activatorRef: EntityReference;
  native let isPlayerActivator: Bool;
}
