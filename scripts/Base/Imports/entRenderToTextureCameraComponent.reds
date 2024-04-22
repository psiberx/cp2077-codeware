public native class entRenderToTextureCameraComponent extends entCameraComponent {
  native let isEnabled: Bool;
  native let virtualCameraName: CName;
  native let dynamicTextureRes: ResourceAsyncRef; // raRef<DynamicTexture>
  native let depthDynamicTextureRes: ResourceRef; // rRef<DynamicTexture>
  native let albedoDynamicTextureRes: ResourceRef; // rRef<DynamicTexture>
  native let normalsDynamicTextureRes: ResourceRef; // rRef<DynamicTexture>
  native let particlesDynamicTextureRes: ResourceRef; // rRef<DynamicTexture>
  native let resolutionWidth: Uint32;
  native let resolutionHeight: Uint32;
  native let aspectRatio: Float;
  native let env: ResourceRef; // rRef<worldEnvironmentAreaParameters>
  native let params: WorldRenderAreaSettings;
  native let renderingMode: entRenderToTextureMode;
  native let depthCutDistance: Float;
  native let backgroundColor: Color;
  native let overrideBackgroundColor: Bool;
  native let renderSceneLayer: RenderSceneLayer;
  native let features: entRenderToTextureFeatures;
  native let streamingDistance: Float;
}
