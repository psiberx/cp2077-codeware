public native class gameuiarcadeRoachRacePlayerController extends inkLogicController {
  native let singleJumpBoost: Vector2;
  native let doubleJumpBoost: Vector2;
  native let gravity: Vector2;
  native let teleportLockoutTime: Float;
  native let carrotPowerupVelocityBoostModifier: Float;
  native let runningBoundingRectangleRelativeSize: Vector2;
  native let jumpingboundingRectangleRelativeSize: Vector2;
  native let poweredupboundingRectangleRelativeSize: Vector2;
  native let invincibilityTime: Float;
  native let invincibilityWarningTime: Float;
  native let roachDeathAnimationTime: Float;
  native let roachDeathAnimationDisplacement: Float;
  native let image: inkImageRef;
  native let jumpSFX: CName;
  native let doubleJumpSFX: CName;
  native let teleportSFX: CName;
  native let invincibilityStartSFX: CName;
  native let invincibilityStopSFX: CName;
  native let carrotPowerupStartSFX: CName;
  native let carrotPowerupStopSFX: CName;
}
