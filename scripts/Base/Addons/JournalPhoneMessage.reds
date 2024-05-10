@addField(JournalPhoneMessage)
native let sender: gameMessageSender;

@addField(JournalPhoneMessage)
native let text: LocalizationString;

@addField(JournalPhoneMessage)
native let imageId: TweakDBID;

@addField(JournalPhoneMessage)
native let delay: Float;

@addField(JournalPhoneMessage)
native let attachment: ref<gameJournalPath>;

@addField(JournalPhoneMessage)
native let isQuestImportant: Bool;

