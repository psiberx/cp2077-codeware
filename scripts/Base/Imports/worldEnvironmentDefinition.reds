public native class worldEnvironmentDefinition extends CResource {
  public native let worldRenderSettings: WorldRenderAreaSettings;
  public native let worldShadowConfig: WorldShadowConfig;
  public native let worldLightingConfig: WorldLightingConfig;
  public native let renderSettingFactors: RenderSettingFactors;
  public native let weatherStates: array<ref<worldWeatherState>>;
  public native let weatherStateTransitions: array<ref<worldWeatherStateTransition>>;
  public native let areaEnvironmentParameterLayers: array<ResourceRef>;
  public native let resourceVersion: Uint8;
}
