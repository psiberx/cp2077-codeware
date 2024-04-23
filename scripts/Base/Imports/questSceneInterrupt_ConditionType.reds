public native class questSceneInterrupt_ConditionType extends questISceneConditionType {
  native let sceneFile: ResourceAsyncRef; // raRef<scnSceneResource>
  native let onlyInSafeMoment: Bool;
  native let interruptConditions: array<ref<scnIInterruptCondition>>;
}
