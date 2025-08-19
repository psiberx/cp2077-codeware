@addField(GameObject)
public native let persistentState: ref<PersistentState>;

@addField(GameObject)
public native let playerSocket: gamePlayerSocket;

@addField(GameObject)
public native let tags: redTagList;

@addField(GameObject)
public native let displayName: LocalizationString;

@addField(GameObject)
public native let displayDescription: LocalizationString;

@addField(GameObject)
public native let audioResourceName: CName;

@addField(GameObject)
public native let visibilityCheckDistance: Float;
