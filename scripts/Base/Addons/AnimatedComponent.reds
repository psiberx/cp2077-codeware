@addField(AnimatedComponent)
public native let controlBinding: ref<entAnimationControlBinding>;

@addField(AnimatedComponent)
public native let rig: ResourceRef; // rRef<animRig>

@addField(AnimatedComponent)
public native let graph: ResourceRef; // rRef<animAnimGraph>

@addField(AnimatedComponent)
public native let animations: animAnimSetup;

@addField(AnimatedComponent)
public native let animTags: redTagList;

@addField(AnimatedComponent)
public native let audioAltName: CName;

@addField(AnimatedComponent)
public native let useLongRangeVisibility: Bool;

@addField(AnimatedComponent)
public native let facialSetup: ResourceAsyncRef; // raRef<animFacialSetup>

@addField(AnimatedComponent)
public native let calculateAccelerationWs: Bool;

@addField(AnimatedComponent)
public native let animParameters: array<entAnimTrackParameter>;

@addField(AnimatedComponent)
public native let serverForcedLod: Int32;

@addField(AnimatedComponent)
public native let clientForcedLod: Int32;

@addField(AnimatedComponent)
public native let serverForcedVisibility: Bool;

@addField(AnimatedComponent)
public native let clientForcedVisibility: Bool;
