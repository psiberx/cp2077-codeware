public native class worldAISpotNode extends worldSocketNode {
  public native let spot: ref<AISpot>;
  public native let isWorkspotInfinite: Bool;
  public native let isWorkspotStatic: Bool;
  public native let markings: array<CName>;
  public native let spotDef: ref<worldTrafficSpotDefinition>;
  public native let disableBumps: Bool;
  public native let lookAtTarget: NodeRef;
  public native let useCrowdWhitelist: Bool;
  public native let useCrowdBlacklist: Bool;
  public native let crowdWhitelist: redTagList;
  public native let crowdBlacklist: redTagList;
}
