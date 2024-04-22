public native struct gameJournalEntryStateChangeDelayData {
  native let entryPath: ref<gameJournalPath>;
  native let entryType: CName;
  native let oldState: gameJournalEntryState;
  native let newState: gameJournalEntryState;
  native let notifyOption: JournalNotifyOption;
  native let changeType: JournalChangeType;
  native let delay: Float;
}
