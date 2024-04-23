public native class worldEnvironmentDefinition extends CResource {
  native let worldRenderSettings: WorldRenderAreaSettings;
  native let worldShadowConfig: WorldShadowConfig;
  native let worldLightingConfig: WorldLightingConfig;
  native let renderSettingFactors: RenderSettingFactors;
  native let weatherStates: array<ref<worldWeatherState>>;
  native let weatherStateTransitions: array<ref<worldWeatherStateTransition>>;
  native let areaEnvironmentParameterLayers: array<ResourceRef>;
  native let resourceVersion: Uint8;
}
