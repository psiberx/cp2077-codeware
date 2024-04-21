public native class gameuiarcadeRoachRaceGameplayController extends gameuiarcadeArcadeGameplayController {
  native let defaultWorldVelocity: Float;
  native let cycleWorldVelocityMultiplier: Float;
  native let carrotPowerupPointsPerSecond: Float;
  native let carrotPowerupTime: Float;
  native let carrotPowerupWorldVelocityMultiplier: Float;
  native let collisionSFX: CName;
  native let powerupPickupSFX: CName;
  native let player: inkWidgetRef;
  native let obstacleSpawner: inkWidgetRef;
  native let background: inkWidgetRef;
  native let currentLevelAndCycleText: inkTextRef;
  native let pointsBoostPickupText: inkTextRef;
  native let dummy: inkWidgetRef;
  native let invincibilityCooldownIndicator: inkWidgetRef;
}
