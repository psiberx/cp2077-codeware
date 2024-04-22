public native class worldGuardAreaNode extends worldAreaShapeNode {
  native let communityEntries: array<AIGuardAreaConnectedCommunity>;
  native let combatCommunityEntries: array<AICombatGuardAreaConnectedCommunity>;
  native let pursuitArea: NodeRef;
  native let pursuitRange: Float;
}
