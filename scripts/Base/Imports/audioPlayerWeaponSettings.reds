public native class audioPlayerWeaponSettings extends audioWeaponSettings {
  native let fireSound: CName;
  native let preFireSound: CName;
  native let burstFireSound: CName;
  native let autoFireSound: CName;
  native let autoFireStop: CName;
  native let timeLimitForAutoFireSingleShot: Float;
  native let padVibrationGain: Float;
  native let padVibrationReloadGain: Float;
  native let tails: CName;
  native let shellCasingsSettings: CName;
  native let animEventOverrides: ref<audioWeaponEventOverrides>;
  native let quickMeleeHitEvent: CName;
  native let initEvent: CName;
  native let shutdownEvent: CName;
  native let aimEnterSound: CName;
  native let aimExitSound: CName;
  native let dryFireSound: CName;
  native let reloadSound: CName;
  native let triggerEffectSingle: CName;
  native let triggerEffectAiming: CName;
  native let triggerEffectAuto: CName;
  native let perfectChargePerkSounds: audioPerfectChargePerkSounds;
}
