@addField(JournalPhoneChoiceEntry)
public native let text: LocalizationString;

@addField(JournalPhoneChoiceEntry)
public native let isQuestImportant: Bool;

@addField(JournalPhoneChoiceEntry)
public native let questCondition: ref<questIBaseCondition>;
