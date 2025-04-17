@addField(GameObject)
native let persistentState: ref<PersistentState>;

@addField(GameObject)
native let playerSocket: gamePlayerSocket;

@addField(GameObject)
native let tags: redTagList;

@addField(GameObject)
native let displayName: LocalizationString;

@addField(GameObject)
native let displayDescription: LocalizationString;

@addField(GameObject)
native let audioResourceName: CName;

@addField(GameObject)
native let visibilityCheckDistance: Float;
