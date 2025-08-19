public native struct gameJournalEntryStateChangeDelayData {
  public native let entryPath: ref<gameJournalPath>;
  public native let entryType: CName;
  public native let oldState: gameJournalEntryState;
  public native let newState: gameJournalEntryState;
  public native let notifyOption: JournalNotifyOption;
  public native let changeType: JournalChangeType;
  public native let delay: Float;
}
