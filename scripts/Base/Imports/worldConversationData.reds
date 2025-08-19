public native class worldConversationData extends ISerializable {
  public native let sceneFilename: ResourceAsyncRef; // raRef<scnSceneResource>
  public native let condition: ref<questIBaseCondition>;
  public native let interruptionOperations: array<ref<scnIInterruptionOperation>>;
  public native let ignoreLocalLimit: Bool;
  public native let ignoreGlobalLimit: Bool;
}
