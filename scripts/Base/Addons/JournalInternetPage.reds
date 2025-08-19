@addField(JournalInternetPage)
public native let address: String;

@addField(JournalInternetPage)
public native let factsToSet: array<JournalFactNameValue>;

@addField(JournalInternetPage)
public native let additionallyFilledFromScripts: Bool;

@addField(JournalInternetPage)
public native let reloadOnZoomIn: Bool;

@addField(JournalInternetPage)
public native let widgetFile: ResourceAsyncRef; // raRef<inkWidgetLibraryResource>

@addField(JournalInternetPage)
public native let scale: Float;

@addField(JournalInternetPage)
public native let texts: array<ref<JournalInternetText>>;

@addField(JournalInternetPage)
public native let rectangles: array<ref<JournalInternetRectangle>>;

@addField(JournalInternetPage)
public native let images: array<ref<JournalInternetImage>>;

@addField(JournalInternetPage)
public native let videos: array<ref<JournalInternetVideo>>;

@addField(JournalInternetPage)
public native let canvases: array<ref<JournalInternetCanvas>>;
