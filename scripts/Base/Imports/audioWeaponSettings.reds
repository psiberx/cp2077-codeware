@mixedRef()
public abstract native class audioWeaponSettings extends audioAudioMetadata {
  public native let bulletType: audioWeaponBulletType;
  public native let shellCasingType: audioWeaponShellCasingType;
  public native let weaponHandlingSettings: audioWeaponHandlingSettings;
  public native let singleShotInSandevistan: Bool;
  public native let chargeStartSound: CName;
  public native let chargeReadySound: CName;
  public native let chargeOverchargeSound: CName;
  public native let chargeDischargeSound: CName;
  public native let fireModeSounds: audioWeaponFireModeSounds;
}
