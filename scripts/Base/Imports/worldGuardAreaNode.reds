public native class worldGuardAreaNode extends worldAreaShapeNode {
  public native let communityEntries: array<AIGuardAreaConnectedCommunity>;
  public native let combatCommunityEntries: array<AICombatGuardAreaConnectedCommunity>;
  public native let pursuitArea: NodeRef;
  public native let pursuitRange: Float;
}
