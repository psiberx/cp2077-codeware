@addField(LightComponent)
public native let type: ELightType;

@addField(LightComponent)
public native let color: Color;

@addField(LightComponent)
public native let radius: Float;

@addField(LightComponent)
public native let unit: ELightUnit;

@addField(LightComponent)
public native let intensity: Float;

@addField(LightComponent)
public native let EV: Float;

@addField(LightComponent)
public native let temperature: Float;

@addField(LightComponent)
public native let sceneDiffuse: Bool;

@addField(LightComponent)
public native let sceneSpecularScale: Uint8;

@addField(LightComponent)
public native let directional: Bool;

@addField(LightComponent)
public native let roughnessBias: Int8;

@addField(LightComponent)
public native let scaleGI: Uint8;

@addField(LightComponent)
public native let scaleEnvProbes: Uint8;

@addField(LightComponent)
public native let useInTransparents: Bool;

@addField(LightComponent)
public native let scaleVolFog: Uint8;

@addField(LightComponent)
public native let useInParticles: Bool;

@addField(LightComponent)
public native let attenuation: rendLightAttenuation;

@addField(LightComponent)
public native let clampAttenuation: Bool;

@addField(LightComponent)
public native let group: rendLightGroup;

@addField(LightComponent)
public native let areaShape: EAreaLightShape;

@addField(LightComponent)
public native let areaTwoSided: Bool;

@addField(LightComponent)
public native let spotCapsule: Bool;

@addField(LightComponent)
public native let sourceRadius: Float;

@addField(LightComponent)
public native let capsuleLength: Float;

@addField(LightComponent)
public native let areaRectSideA: Float;

@addField(LightComponent)
public native let areaRectSideB: Float;

@addField(LightComponent)
public native let innerAngle: Float;

@addField(LightComponent)
public native let outerAngle: Float;

@addField(LightComponent)
public native let softness: Float;

@addField(LightComponent)
public native let enableLocalShadows: Bool;

@addField(LightComponent)
public native let enableLocalShadowsForceStaticsOnly: Bool;

@addField(LightComponent)
public native let contactShadows: rendContactShadowReciever;

@addField(LightComponent)
public native let shadowAngle: Float;

@addField(LightComponent)
public native let shadowRadius: Float;

@addField(LightComponent)
public native let shadowFadeDistance: Float;

@addField(LightComponent)
public native let shadowFadeRange: Float;

@addField(LightComponent)
public native let shadowSoftnessMode: ELightShadowSoftnessMode;

@addField(LightComponent)
public native let rayTracedShadowsPlatform: rendRayTracedShadowsPlatform;

@addField(LightComponent)
public native let rayTracingLightSourceRadius: Float;

@addField(LightComponent)
public native let rayTracingContactShadowRange: Float;

@addField(LightComponent)
public native let iesProfile: ResourceAsyncRef; // raRef<CIESDataResource>

@addField(LightComponent)
public native let flicker: rendSLightFlickering;

@addField(LightComponent)
public native let envColorGroup: EEnvColorGroup;

@addField(LightComponent)
public native let colorGroupSaturation: Uint8;

@addField(LightComponent)
public native let portalAngleCutoff: Uint8;

@addField(LightComponent)
public native let allowDistantLight: Bool;

@addField(LightComponent)
public native let rayTracingIntensityScale: Float;

@addField(LightComponent)
public native let pathTracingLightUsage: rendEPathTracingLightUsage;

@addField(LightComponent)
public native let pathTracingOverrideScaleGI: Bool;

@addField(LightComponent)
public native let rtxdiShadowStartingDistance: Float;

@addField(LightComponent)
public native let isEnabled: Bool;
