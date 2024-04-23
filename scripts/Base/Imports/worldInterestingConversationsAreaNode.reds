public native class worldInterestingConversationsAreaNode extends worldTriggerAreaNode {
  native let conversationGroups: array<ResourceRef>;
  native let conversationResources: array<ref<worldConversationGroupData>>;
  native let conversations: array<ref<worldConversationData>>;
  native let workspots: array<NodeRef>;
  native let savingStrategy: audioConversationSavingStrategy;
}
