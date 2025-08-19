public native struct audioVehicleWheelData {
  public native let wheelStartEvents: array<CName>;
  public native let wheelStopEvents: array<CName>;
  public native let wheelRegularSuspensionImpacts: array<CName>;
  public native let wheelLandingSuspensionImpacts: array<CName>;
  public native let suspensionPressureMultiplier: Float;
  public native let landingSuspensionPressureMultiplier: Float;
  public native let suspensionPressureLimit: Float;
  public native let minSuspensionPressureThreshold: Float;
  public native let suspensionImpactCooldown: Float;
  public native let minWheelTimeInAirBeforeLanding: Float;
}
