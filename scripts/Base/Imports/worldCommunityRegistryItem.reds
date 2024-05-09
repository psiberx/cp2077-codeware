public native struct worldCommunityRegistryItem {
  native let entriesInitialState: array<worldCommunityEntryInitialState>;
  native let template: ref<communityCommunityTemplateData>;
  native let communityId: gameCommunityID;
  native let communityAreaType: worldCommunityRegistryItemAreaNodeType;
}
