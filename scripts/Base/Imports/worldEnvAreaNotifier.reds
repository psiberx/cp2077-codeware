public native class worldEnvAreaNotifier extends worldITriggerAreaNotifer {
  public native let priority: Uint8;
  public native let horizontalFadeDistance: Float;
  public native let verticalFadeDistance: Float;
  public native let blendTimeIn: Float;
  public native let blendTimeOut: Float;
  public native let env: ResourceRef; // rRef<worldEnvironmentAreaParameters>
  public native let params: WorldRenderAreaSettings;
  public native let weatherStateNames: array<CName>;
  public native let weatherStateValues: array<Bool>;
  public native let resourceVersion: Uint8;
}
