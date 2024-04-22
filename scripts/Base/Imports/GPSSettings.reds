public native struct GPSSettings {
  native let lineEffectOnFoot: ResourceAsyncRef; // raRef<worldEffect>
  native let lineEffectVehicle: ResourceAsyncRef; // raRef<worldEffect>
  native let fixedPathOffset: Vector3;
  native let fixedPortalMappinOffset: Vector3;
  native let pathRefreshTimeInterval: Float;
  native let lastPlayerNavmeshPositionRefreshTimeIntervalSecs: Float;
  native let maxPathDisplayLength: Float;
}
