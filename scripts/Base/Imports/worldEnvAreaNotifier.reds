public native class worldEnvAreaNotifier extends worldITriggerAreaNotifer {
  native let priority: Uint8;
  native let horizontalFadeDistance: Float;
  native let verticalFadeDistance: Float;
  native let blendTimeIn: Float;
  native let blendTimeOut: Float;
  native let env: ResourceRef; // rRef<worldEnvironmentAreaParameters>
  native let params: WorldRenderAreaSettings;
  native let weatherStateNames: array<CName>;
  native let weatherStateValues: array<Bool>;
  native let resourceVersion: Uint8;
}
