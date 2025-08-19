@addField(JournalEmail)
public native let sender: LocalizationString;

@addField(JournalEmail)
public native let addressee: LocalizationString;

@addField(JournalEmail)
public native let title: LocalizationString;

@addField(JournalEmail)
public native let content: LocalizationString;

@addField(JournalEmail)
public native let videoResource: ResourceAsyncRef; // raRef<Bink>

@addField(JournalEmail)
public native let pictureTweak: TweakDBID;
