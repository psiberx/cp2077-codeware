public native class questJournalBulkUpdate_NodeType extends questIJournal_NodeType {
  native let path: ref<gameJournalPath>;
  native let requiredEntryType: CName;
  native let requiredEntryState: CName;
  native let newEntryState: CName;
  native let sendNotification: Bool;
  native let propagateChange: Bool;
}
