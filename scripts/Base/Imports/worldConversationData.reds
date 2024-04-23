public native class worldConversationData extends ISerializable {
  native let sceneFilename: ResourceAsyncRef; // raRef<scnSceneResource>
  native let condition: ref<questIBaseCondition>;
  native let interruptionOperations: array<ref<scnIInterruptionOperation>>;
  native let ignoreLocalLimit: Bool;
  native let ignoreGlobalLimit: Bool;
}
