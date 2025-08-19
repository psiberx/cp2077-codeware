@addField(JournalPhoneMessage)
public native let sender: gameMessageSender;

@addField(JournalPhoneMessage)
public native let text: LocalizationString;

@addField(JournalPhoneMessage)
public native let imageId: TweakDBID;

@addField(JournalPhoneMessage)
public native let delay: Float;

@addField(JournalPhoneMessage)
public native let attachment: ref<gameJournalPath>;

@addField(JournalPhoneMessage)
public native let isQuestImportant: Bool;
