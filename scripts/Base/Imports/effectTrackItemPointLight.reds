public native class effectTrackItemPointLight extends effectTrackItem {
  public native let tint: effectEffectParameterEvaluatorColor;
  public native let intensity: effectEffectParameterEvaluatorFloat;
  public native let EV: Float;
  public native let radius: effectEffectParameterEvaluatorFloat;
  public native let offset: Vector3;
  public native let color: Color;
  public native let envColorGroup: EEnvColorGroup;
  public native let colorGroupSaturation: Uint8;
  public native let roughnessBias: Int8;
  public native let useInGI: Bool;
  public native let useInVolFog: Bool;
  public native let useInTransparents: Bool;
  public native let useInParticles: Bool;
  public native let sceneDiffuse: Bool;
  public native let sceneSpecular: Bool;
  public native let clampAttenuation: Bool;
  public native let flicker: rendSLightFlickering;
}
