@addField(LightComponent)
native let type: ELightType;

@addField(LightComponent)
native let color: Color;

@addField(LightComponent)
native let radius: Float;

@addField(LightComponent)
native let unit: ELightUnit;

@addField(LightComponent)
native let intensity: Float;

@addField(LightComponent)
native let EV: Float;

@addField(LightComponent)
native let temperature: Float;

@addField(LightComponent)
native let sceneDiffuse: Bool;

@addField(LightComponent)
native let sceneSpecularScale: Uint8;

@addField(LightComponent)
native let directional: Bool;

@addField(LightComponent)
native let roughnessBias: Int8;

@addField(LightComponent)
native let scaleGI: Uint8;

@addField(LightComponent)
native let scaleEnvProbes: Uint8;

@addField(LightComponent)
native let useInTransparents: Bool;

@addField(LightComponent)
native let scaleVolFog: Uint8;

@addField(LightComponent)
native let useInParticles: Bool;

@addField(LightComponent)
native let attenuation: rendLightAttenuation;

@addField(LightComponent)
native let clampAttenuation: Bool;

@addField(LightComponent)
native let group: rendLightGroup;

@addField(LightComponent)
native let areaShape: EAreaLightShape;

@addField(LightComponent)
native let areaTwoSided: Bool;

@addField(LightComponent)
native let spotCapsule: Bool;

@addField(LightComponent)
native let sourceRadius: Float;

@addField(LightComponent)
native let capsuleLength: Float;

@addField(LightComponent)
native let areaRectSideA: Float;

@addField(LightComponent)
native let areaRectSideB: Float;

@addField(LightComponent)
native let innerAngle: Float;

@addField(LightComponent)
native let outerAngle: Float;

@addField(LightComponent)
native let softness: Float;

@addField(LightComponent)
native let enableLocalShadows: Bool;

@addField(LightComponent)
native let enableLocalShadowsForceStaticsOnly: Bool;

@addField(LightComponent)
native let contactShadows: rendContactShadowReciever;

@addField(LightComponent)
native let shadowAngle: Float;

@addField(LightComponent)
native let shadowRadius: Float;

@addField(LightComponent)
native let shadowFadeDistance: Float;

@addField(LightComponent)
native let shadowFadeRange: Float;

@addField(LightComponent)
native let shadowSoftnessMode: ELightShadowSoftnessMode;

@addField(LightComponent)
native let rayTracedShadowsPlatform: rendRayTracedShadowsPlatform;

@addField(LightComponent)
native let rayTracingLightSourceRadius: Float;

@addField(LightComponent)
native let rayTracingContactShadowRange: Float;

@addField(LightComponent)
native let iesProfile: ResourceAsyncRef; // raRef<CIESDataResource>

@addField(LightComponent)
native let flicker: rendSLightFlickering;

@addField(LightComponent)
native let envColorGroup: EEnvColorGroup;

@addField(LightComponent)
native let colorGroupSaturation: Uint8;

@addField(LightComponent)
native let portalAngleCutoff: Uint8;

@addField(LightComponent)
native let allowDistantLight: Bool;

@addField(LightComponent)
native let rayTracingIntensityScale: Float;

@addField(LightComponent)
native let pathTracingLightUsage: rendEPathTracingLightUsage;

@addField(LightComponent)
native let pathTracingOverrideScaleGI: Bool;

@addField(LightComponent)
native let rtxdiShadowStartingDistance: Float;

@addField(LightComponent)
native let isEnabled: Bool;

