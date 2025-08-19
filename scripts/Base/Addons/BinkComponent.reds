@addField(BinkComponent)
public native let meshTargetBinding: ref<gameBinkMeshTargetBinding>;

@addField(BinkComponent)
public native let videoPlayerName: CName;

@addField(BinkComponent)
public native let binkResource: ResourceAsyncRef; // raRef<Bink>

@addField(BinkComponent)
public native let audioEvent: CName;

@addField(BinkComponent)
public native let loopVideo: Bool;

@addField(BinkComponent)
public native let forceVideoFrameRate: Bool;

@addField(BinkComponent)
public native let isEnabled: Bool;
