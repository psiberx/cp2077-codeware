@addField(JournalFile)
public native let title: LocalizationString;

@addField(JournalFile)
public native let content: LocalizationString;

@addField(JournalFile)
public native let videoResource: ResourceAsyncRef; // raRef<Bink>

@addField(JournalFile)
public native let pictureTweak: TweakDBID;
