public native class gamePhotoModeBackgroundCameraComponent extends entCameraComponent {
  public native let isEnabled: Bool;
  public native let virtualCameraName: CName;
  public native let dynamicTextureRes: ResourceAsyncRef; // raRef<DynamicTexture>
  public native let env: ResourceRef; // rRef<worldEnvironmentAreaParameters>
  public native let params: WorldRenderAreaSettings;
  public native let depthCutDistance: Float;
  public native let backgroundColor: Color;
  public native let overrideBackgroundColor: Bool;
  public native let renderSceneLayer: RenderSceneLayer;
  public native let streamingDistance: Float;
}
