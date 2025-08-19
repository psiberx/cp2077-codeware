public native class questSceneInterrupt_ConditionType extends questISceneConditionType {
  public native let sceneFile: ResourceAsyncRef; // raRef<scnSceneResource>
  public native let onlyInSafeMoment: Bool;
  public native let interruptConditions: array<ref<scnIInterruptCondition>>;
}
