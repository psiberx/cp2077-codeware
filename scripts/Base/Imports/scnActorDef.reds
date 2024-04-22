public native struct scnActorDef {
  native let actorId: scnActorId;
  native let voicetagId: scnVoicetagId;
  native let acquisitionPlan: scnEntityAcquisitionPlan;
  native let findActorInContextParams: scnFindEntityInContextParams;
  native let findActorInWorldParams: scnFindEntityInWorldParams;
  native let spawnDespawnParams: scnSpawnDespawnEntityParams;
  native let spawnSetParams: scnSpawnSetParams;
  native let communityParams: scnCommunityParams;
  native let spawnerParams: scnSpawnerParams;
  native let animSets: array<scnSRRefId>;
  native let lipsyncAnimSet: scnLipsyncAnimSetSRRefId;
  native let facialAnimSets: array<scnRidFacialAnimSetSRRefId>;
  native let cyberwareAnimSets: array<scnRidCyberwareAnimSetSRRefId>;
  native let deformationAnimSets: array<scnRidDeformationAnimSetSRRefId>;
  native let bodyCinematicAnimSets: array<scnCinematicAnimSetSRRefId>;
  native let facialCinematicAnimSets: array<scnCinematicAnimSetSRRefId>;
  native let cyberwareCinematicAnimSets: array<scnCinematicAnimSetSRRefId>;
  native let dynamicAnimSets: array<scnDynamicAnimSetSRRefId>;
  native let holocallInitScn: ResourceAsyncRef; // raRef<CResource>
  native let actorName: String;
  native let specCharacterRecordId: TweakDBID;
  native let specAppearance: CName;
}
