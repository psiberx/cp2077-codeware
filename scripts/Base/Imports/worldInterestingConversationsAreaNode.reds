public native class worldInterestingConversationsAreaNode extends worldTriggerAreaNode {
  public native let conversationGroups: array<ResourceRef>;
  public native let conversationResources: array<ref<worldConversationGroupData>>;
  public native let conversations: array<ref<worldConversationData>>;
  public native let workspots: array<NodeRef>;
  public native let savingStrategy: audioConversationSavingStrategy;
}
