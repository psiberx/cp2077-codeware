public native class worldCommunityRegistryNode extends worldNode {
  public native let spawnSetNameToCommunityID: gameCommunitySpawnSetNameToID;
  public native let crowdCreationRegistry: ref<gameCrowdCreationDataRegistry>;
  public native let communitiesData: array<worldCommunityRegistryItem>;
  public native let workspotsPersistentData: array<AISpotPersistentData>;
  public native let representsCrowd: Bool;
}
