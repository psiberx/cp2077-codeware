public native struct audioVehicleWheelData {
  native let wheelStartEvents: array<CName>;
  native let wheelStopEvents: array<CName>;
  native let wheelRegularSuspensionImpacts: array<CName>;
  native let wheelLandingSuspensionImpacts: array<CName>;
  native let suspensionPressureMultiplier: Float;
  native let landingSuspensionPressureMultiplier: Float;
  native let suspensionPressureLimit: Float;
  native let minSuspensionPressureThreshold: Float;
  native let suspensionImpactCooldown: Float;
  native let minWheelTimeInAirBeforeLanding: Float;
}
