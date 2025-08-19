public native class gameuiarcadeRoachRaceGameplayController extends gameuiarcadeArcadeGameplayController {
  public native let defaultWorldVelocity: Float;
  public native let cycleWorldVelocityMultiplier: Float;
  public native let carrotPowerupPointsPerSecond: Float;
  public native let carrotPowerupTime: Float;
  public native let carrotPowerupWorldVelocityMultiplier: Float;
  public native let collisionSFX: CName;
  public native let powerupPickupSFX: CName;
  public native let player: inkWidgetRef;
  public native let obstacleSpawner: inkWidgetRef;
  public native let background: inkWidgetRef;
  public native let currentLevelAndCycleText: inkTextRef;
  public native let pointsBoostPickupText: inkTextRef;
  public native let dummy: inkWidgetRef;
  public native let invincibilityCooldownIndicator: inkWidgetRef;
}
