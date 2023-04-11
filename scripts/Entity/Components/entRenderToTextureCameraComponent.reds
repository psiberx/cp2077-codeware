public native class entRenderToTextureCameraComponent extends entCameraComponent {
  native let isEnabled: Bool;
  native let virtualCameraName: CName;
  native let dynamicTextureRes: ResourceAsyncRef;
  native let depthDynamicTextureRes: ResourceRef;
  native let albedoDynamicTextureRes: ResourceRef;
  native let normalsDynamicTextureRes: ResourceRef;
  native let particlesDynamicTextureRes: ResourceRef;
  native let resolutionWidth: Uint32;
  native let resolutionHeight: Uint32;
  native let aspectRatio: Float;
  native let env: ResourceRef;
  native let params: WorldRenderAreaSettings;
  native let renderingMode: entRenderToTextureMode;
  native let depthCutDistance: Float;
  native let backgroundColor: Color;
  native let overrideBackgroundColor: Bool;
  native let renderSceneLayer: RenderSceneLayer;
  native let features: entRenderToTextureFeatures;
  native let streamingDistance: Float;
}
