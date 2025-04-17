@addField(JournalInternetPage)
native let address: String;

@addField(JournalInternetPage)
native let factsToSet: array<JournalFactNameValue>;

@addField(JournalInternetPage)
native let additionallyFilledFromScripts: Bool;

@addField(JournalInternetPage)
native let reloadOnZoomIn: Bool;

@addField(JournalInternetPage)
native let widgetFile: ResourceAsyncRef; // raRef<inkWidgetLibraryResource>

@addField(JournalInternetPage)
native let scale: Float;

@addField(JournalInternetPage)
native let texts: array<ref<JournalInternetText>>;

@addField(JournalInternetPage)
native let rectangles: array<ref<JournalInternetRectangle>>;

@addField(JournalInternetPage)
native let images: array<ref<JournalInternetImage>>;

@addField(JournalInternetPage)
native let videos: array<ref<JournalInternetVideo>>;

@addField(JournalInternetPage)
native let canvases: array<ref<JournalInternetCanvas>>;
