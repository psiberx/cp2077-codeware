@addField(JournalInternetSite)
public native let shortName: LocalizationString;

@addField(JournalInternetSite)
public native let mainPagePath: ref<gameJournalPath>;

@addField(JournalInternetSite)
public native let ignoredAtDesktop: Bool;

@addField(JournalInternetSite)
public native let textureAtlas: ResourceAsyncRef; // raRef<inkTextureAtlas>

@addField(JournalInternetSite)
public native let texturePart: CName;
