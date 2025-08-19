public native class JournalPointOfInterestMappin extends JournalEntry {
  public native let staticNodeRef: NodeRef;
  public native let dynamicEntityRef: EntityReference;
  public native let securityAreaRef: NodeRef;
  public native let mappinData: PointOfInterestMappinData;
  public native let offset: Vector3;
  public native let questPath: ref<gameJournalPath>;
  public native let recommendedLevelID: TweakDBID;
  public native let notificationTriggerAreaRef: NodeRef;
}
