public native class worldConversationGroupData extends ISerializable {
  public native let conversationGroup: ResourceRef; // rRef<scnInterestingConversationsResource>
  public native let interruptionOperations: array<ref<scnIInterruptionOperation>>;
  public native let ignoreLocalLimit: Bool;
  public native let ignoreGlobalLimit: Bool;
}
