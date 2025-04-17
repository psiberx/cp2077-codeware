@addField(AnimatedComponent)
native let controlBinding: ref<entAnimationControlBinding>;

@addField(AnimatedComponent)
native let rig: ResourceRef; // rRef<animRig>

@addField(AnimatedComponent)
native let graph: ResourceRef; // rRef<animAnimGraph>

@addField(AnimatedComponent)
native let animations: animAnimSetup;

@addField(AnimatedComponent)
native let animTags: redTagList;

@addField(AnimatedComponent)
native let audioAltName: CName;

@addField(AnimatedComponent)
native let useLongRangeVisibility: Bool;

@addField(AnimatedComponent)
native let facialSetup: ResourceAsyncRef; // raRef<animFacialSetup>

@addField(AnimatedComponent)
native let calculateAccelerationWs: Bool;

@addField(AnimatedComponent)
native let animParameters: array<entAnimTrackParameter>;

@addField(AnimatedComponent)
native let serverForcedLod: Int32;

@addField(AnimatedComponent)
native let clientForcedLod: Int32;

@addField(AnimatedComponent)
native let serverForcedVisibility: Bool;

@addField(AnimatedComponent)
native let clientForcedVisibility: Bool;
