public abstract native class audioWeaponSettings extends audioAudioMetadata {
  native let bulletType: audioWeaponBulletType;
  native let shellCasingType: audioWeaponShellCasingType;
  native let weaponHandlingSettings: audioWeaponHandlingSettings;
  native let singleShotInSandevistan: Bool;
  native let chargeStartSound: CName;
  native let chargeReadySound: CName;
  native let chargeOverchargeSound: CName;
  native let chargeDischargeSound: CName;
  native let fireModeSounds: audioWeaponFireModeSounds;
}
