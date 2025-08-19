public native struct GPSSettings {
  public native let lineEffectOnFoot: ResourceAsyncRef; // raRef<worldEffect>
  public native let lineEffectVehicle: ResourceAsyncRef; // raRef<worldEffect>
  public native let fixedPathOffset: Vector3;
  public native let fixedPortalMappinOffset: Vector3;
  public native let pathRefreshTimeInterval: Float;
  public native let lastPlayerNavmeshPositionRefreshTimeIntervalSecs: Float;
  public native let maxPathDisplayLength: Float;
}
