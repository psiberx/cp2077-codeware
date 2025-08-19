@mixedRef()
public native class audioPlayerWeaponSettings extends audioWeaponSettings {
  public native let fireSound: CName;
  public native let preFireSound: CName;
  public native let burstFireSound: CName;
  public native let autoFireSound: CName;
  public native let autoFireStop: CName;
  public native let timeLimitForAutoFireSingleShot: Float;
  public native let padVibrationGain: Float;
  public native let padVibrationReloadGain: Float;
  public native let tails: CName;
  public native let shellCasingsSettings: CName;
  public native let animEventOverrides: ref<audioWeaponEventOverrides>;
  public native let quickMeleeHitEvent: CName;
  public native let initEvent: CName;
  public native let shutdownEvent: CName;
  public native let aimEnterSound: CName;
  public native let aimExitSound: CName;
  public native let dryFireSound: CName;
  public native let reloadSound: CName;
  public native let triggerEffectSingle: CName;
  public native let triggerEffectAiming: CName;
  public native let triggerEffectAuto: CName;
  public native let perfectChargePerkSounds: audioPerfectChargePerkSounds;
}
