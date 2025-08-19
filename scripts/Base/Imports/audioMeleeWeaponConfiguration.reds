@mixedRef()
public native class audioMeleeWeaponConfiguration extends audioAudioMetadata {
  public native let fastWhoosh: audioMeleeSound;
  public native let normalWhoosh: audioMeleeSound;
  public native let slowWhoosh: audioMeleeSound;
  public native let detailSound: audioMeleeSound;
  public native let handlingSound: audioMeleeSound;
  public native let equipSound: audioMeleeSound;
  public native let unequipSound: audioMeleeSound;
  public native let blockSound: audioMeleeSound;
  public native let parrySound: audioMeleeSound;
  public native let attackChargedThreshold: Float;
  public native let attackChargedSound: audioMeleeSound;
  public native let attackDischargedSound: audioMeleeSound;
  public native let meleeSoundsByHitPerMaterialType: ref<audioMeleeHitTypeMeleeSoundDictionary>;
  public native let meleeWeaponConfigurationsByRigTypeMap: audioMeleeRigTypeMeleeWeaponConfigurationMap;
}
