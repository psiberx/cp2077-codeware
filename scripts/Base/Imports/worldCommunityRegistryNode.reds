public native class worldCommunityRegistryNode extends worldNode {
  native let spawnSetNameToCommunityID: gameCommunitySpawnSetNameToID;
  native let crowdCreationRegistry: ref<gameCrowdCreationDataRegistry>;
  native let communitiesData: array<worldCommunityRegistryItem>;
  native let workspotsPersistentData: array<AISpotPersistentData>;
  native let representsCrowd: Bool;
}
