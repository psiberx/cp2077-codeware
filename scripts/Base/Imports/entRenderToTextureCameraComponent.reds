public native class entRenderToTextureCameraComponent extends entCameraComponent {
  public native let isEnabled: Bool;
  public native let virtualCameraName: CName;
  public native let dynamicTextureRes: ResourceAsyncRef; // raRef<DynamicTexture>
  public native let depthDynamicTextureRes: ResourceRef; // rRef<DynamicTexture>
  public native let albedoDynamicTextureRes: ResourceRef; // rRef<DynamicTexture>
  public native let normalsDynamicTextureRes: ResourceRef; // rRef<DynamicTexture>
  public native let particlesDynamicTextureRes: ResourceRef; // rRef<DynamicTexture>
  public native let resolutionWidth: Uint32;
  public native let resolutionHeight: Uint32;
  public native let aspectRatio: Float;
  public native let env: ResourceRef; // rRef<worldEnvironmentAreaParameters>
  public native let params: WorldRenderAreaSettings;
  public native let renderingMode: entRenderToTextureMode;
  public native let depthCutDistance: Float;
  public native let backgroundColor: Color;
  public native let overrideBackgroundColor: Bool;
  public native let renderSceneLayer: RenderSceneLayer;
  public native let features: entRenderToTextureFeatures;
  public native let streamingDistance: Float;
}
