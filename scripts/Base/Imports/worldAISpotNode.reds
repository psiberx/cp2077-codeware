public native class worldAISpotNode extends worldSocketNode {
  native let spot: ref<AISpot>;
  native let isWorkspotInfinite: Bool;
  native let isWorkspotStatic: Bool;
  native let markings: array<CName>;
  native let spotDef: ref<worldTrafficSpotDefinition>;
  native let disableBumps: Bool;
  native let lookAtTarget: NodeRef;
  native let useCrowdWhitelist: Bool;
  native let useCrowdBlacklist: Bool;
  native let crowdWhitelist: redTagList;
  native let crowdBlacklist: redTagList;
}
