public native class audioMeleeWeaponConfiguration extends audioAudioMetadata {
  native let fastWhoosh: audioMeleeSound;
  native let normalWhoosh: audioMeleeSound;
  native let slowWhoosh: audioMeleeSound;
  native let detailSound: audioMeleeSound;
  native let handlingSound: audioMeleeSound;
  native let equipSound: audioMeleeSound;
  native let unequipSound: audioMeleeSound;
  native let blockSound: audioMeleeSound;
  native let parrySound: audioMeleeSound;
  native let attackChargedThreshold: Float;
  native let attackChargedSound: audioMeleeSound;
  native let attackDischargedSound: audioMeleeSound;
  native let meleeSoundsByHitPerMaterialType: ref<audioMeleeHitTypeMeleeSoundDictionary>;
  native let meleeWeaponConfigurationsByRigTypeMap: audioMeleeRigTypeMeleeWeaponConfigurationMap;
}
