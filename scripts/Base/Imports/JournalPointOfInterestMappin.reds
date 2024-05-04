public native class JournalPointOfInterestMappin extends JournalEntry {
  native let staticNodeRef: NodeRef;
  native let dynamicEntityRef: EntityReference;
  native let securityAreaRef: NodeRef;
  native let mappinData: PointOfInterestMappinData;
  native let offset: Vector3;
  native let questPath: ref<gameJournalPath>;
  native let recommendedLevelID: TweakDBID;
  native let notificationTriggerAreaRef: NodeRef;
}
