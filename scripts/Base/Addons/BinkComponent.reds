@addField(BinkComponent)
native let meshTargetBinding: ref<gameBinkMeshTargetBinding>;

@addField(BinkComponent)
native let videoPlayerName: CName;

@addField(BinkComponent)
native let binkResource: ResourceAsyncRef; // raRef<Bink>

@addField(BinkComponent)
native let audioEvent: CName;

@addField(BinkComponent)
native let loopVideo: Bool;

@addField(BinkComponent)
native let forceVideoFrameRate: Bool;

@addField(BinkComponent)
native let isEnabled: Bool;
