public native class questSceneReturn_ConditionType extends questISceneConditionType {
  native let sceneFile: ResourceAsyncRef; // raRef<scnSceneResource>
  native let SceneVersion: scnSceneVersionCheck;
  native let returnConditions: array<ref<scnIReturnCondition>>;
}
