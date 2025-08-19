public native class questJournalBulkUpdate_NodeType extends questIJournal_NodeType {
  public native let path: ref<gameJournalPath>;
  public native let requiredEntryType: CName;
  public native let requiredEntryState: CName;
  public native let newEntryState: CName;
  public native let sendNotification: Bool;
  public native let propagateChange: Bool;
}
