@addField(SceneAnimationMotionActionParams)
public native let motionType: gameSceneAnimationMotionActionParamsMotionType;

@addField(SceneAnimationMotionActionParams)
public native let motionBlendInTime: Float;

@addField(SceneAnimationMotionActionParams)
public native let blendInCurve: gameSceneAnimationMotionActionParamsEasingType;

@addField(SceneAnimationMotionActionParams)
public native let initialDt: Float;

@addField(SceneAnimationMotionActionParams)
public native let globalTimeToAnimTime: Float;

@addField(SceneAnimationMotionActionParams)
public native let mountDescriptor: gameMountDescriptor;

@addField(SceneAnimationMotionActionParams)
public native let playerParams: gameScenePlayerAnimationParams;

@addField(SceneAnimationMotionActionParams)
public native let trajectoryLOD: array<scnAnimationMotionSample>;

@addField(SceneAnimationMotionActionParams)
public native let dynamicAnimSetupHash: Uint64;
