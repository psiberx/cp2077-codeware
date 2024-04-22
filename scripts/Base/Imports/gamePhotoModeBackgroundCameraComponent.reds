public native class gamePhotoModeBackgroundCameraComponent extends entCameraComponent {
  native let isEnabled: Bool;
  native let virtualCameraName: CName;
  native let dynamicTextureRes: ResourceAsyncRef; // raRef<DynamicTexture>
  native let env: ResourceRef; // rRef<worldEnvironmentAreaParameters>
  native let params: WorldRenderAreaSettings;
  native let depthCutDistance: Float;
  native let backgroundColor: Color;
  native let overrideBackgroundColor: Bool;
  native let renderSceneLayer: RenderSceneLayer;
  native let streamingDistance: Float;
}
