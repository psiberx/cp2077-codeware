public native class worldConversationGroupData extends ISerializable {
  native let conversationGroup: ResourceRef; // rRef<scnInterestingConversationsResource>
  native let interruptionOperations: array<ref<scnIInterruptionOperation>>;
  native let ignoreLocalLimit: Bool;
  native let ignoreGlobalLimit: Bool;
}
