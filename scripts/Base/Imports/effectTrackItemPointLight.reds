public native class effectTrackItemPointLight extends effectTrackItem {
  native let tint: effectEffectParameterEvaluatorColor;
  native let intensity: effectEffectParameterEvaluatorFloat;
  native let EV: Float;
  native let radius: effectEffectParameterEvaluatorFloat;
  native let offset: Vector3;
  native let color: Color;
  native let envColorGroup: EEnvColorGroup;
  native let colorGroupSaturation: Uint8;
  native let roughnessBias: Int8;
  native let useInGI: Bool;
  native let useInVolFog: Bool;
  native let useInTransparents: Bool;
  native let useInParticles: Bool;
  native let sceneDiffuse: Bool;
  native let sceneSpecular: Bool;
  native let clampAttenuation: Bool;
  native let flicker: rendSLightFlickering;
}
