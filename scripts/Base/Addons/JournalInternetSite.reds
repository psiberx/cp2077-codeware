@addField(JournalInternetSite)
native let shortName: LocalizationString;

@addField(JournalInternetSite)
native let mainPagePath: ref<gameJournalPath>;

@addField(JournalInternetSite)
native let ignoredAtDesktop: Bool;

@addField(JournalInternetSite)
native let textureAtlas: ResourceAsyncRef; // raRef<inkTextureAtlas>

@addField(JournalInternetSite)
native let texturePart: CName;
