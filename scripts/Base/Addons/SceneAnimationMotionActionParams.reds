@addField(SceneAnimationMotionActionParams)
native let motionType: gameSceneAnimationMotionActionParamsMotionType;

@addField(SceneAnimationMotionActionParams)
native let motionBlendInTime: Float;

@addField(SceneAnimationMotionActionParams)
native let blendInCurve: gameSceneAnimationMotionActionParamsEasingType;

@addField(SceneAnimationMotionActionParams)
native let initialDt: Float;

@addField(SceneAnimationMotionActionParams)
native let globalTimeToAnimTime: Float;

@addField(SceneAnimationMotionActionParams)
native let mountDescriptor: gameMountDescriptor;

@addField(SceneAnimationMotionActionParams)
native let playerParams: gameScenePlayerAnimationParams;

@addField(SceneAnimationMotionActionParams)
native let trajectoryLOD: array<scnAnimationMotionSample>;

@addField(SceneAnimationMotionActionParams)
native let dynamicAnimSetupHash: Uint64;
