public native struct gameWeaponReplicationHistory {
  public native let weaponSlot: TweakDBID;
  public native let shots: [gameReplicatedShotData; 8];
  public native let latestShotId: Uint32;
  public native let continuousAttack: gameReplicatedContinuousAttack;
}
