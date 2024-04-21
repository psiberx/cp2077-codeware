public native struct scnPlayerActorDef {
  native let actorId: scnActorId;
  native let specTemplate: CName;
  native let specCharacterRecordId: TweakDBID;
  native let specAppearance: CName;
  native let voicetagId: scnVoicetagId;
  native let animSets: array<scnSRRefId>;
  native let lipsyncAnimSet: scnLipsyncAnimSetSRRefId;
  native let facialAnimSets: array<scnRidFacialAnimSetSRRefId>;
  native let cyberwareAnimSets: array<scnRidCyberwareAnimSetSRRefId>;
  native let deformationAnimSets: array<scnRidDeformationAnimSetSRRefId>;
  native let bodyCinematicAnimSets: array<scnCinematicAnimSetSRRefId>;
  native let facialCinematicAnimSets: array<scnCinematicAnimSetSRRefId>;
  native let cyberwareCinematicAnimSets: array<scnCinematicAnimSetSRRefId>;
  native let dynamicAnimSets: array<scnDynamicAnimSetSRRefId>;
  native let acquisitionPlan: scnEntityAcquisitionPlan;
  native let findNetworkPlayerParams: scnFindNetworkPlayerParams;
  native let findActorInContextParams: scnFindEntityInContextParams;
  native let playerName: String;
}
