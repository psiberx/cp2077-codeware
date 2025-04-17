@addField(JournalPhoneChoiceEntry)
native let text: LocalizationString;

@addField(JournalPhoneChoiceEntry)
native let isQuestImportant: Bool;

@addField(JournalPhoneChoiceEntry)
native let questCondition: ref<questIBaseCondition>;
