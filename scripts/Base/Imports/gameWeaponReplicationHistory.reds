public native struct gameWeaponReplicationHistory {
  native let weaponSlot: TweakDBID;
  native let shots: [gameReplicatedShotData; 8];
  native let latestShotId: Uint32;
  native let continuousAttack: gameReplicatedContinuousAttack;
}
