public native struct scnActorDef {
  public native let actorId: scnActorId;
  public native let voicetagId: scnVoicetagId;
  public native let acquisitionPlan: scnEntityAcquisitionPlan;
  public native let findActorInContextParams: scnFindEntityInContextParams;
  public native let findActorInWorldParams: scnFindEntityInWorldParams;
  public native let spawnDespawnParams: scnSpawnDespawnEntityParams;
  public native let spawnSetParams: scnSpawnSetParams;
  public native let communityParams: scnCommunityParams;
  public native let spawnerParams: scnSpawnerParams;
  public native let animSets: array<scnSRRefId>;
  public native let lipsyncAnimSet: scnLipsyncAnimSetSRRefId;
  public native let facialAnimSets: array<scnRidFacialAnimSetSRRefId>;
  public native let cyberwareAnimSets: array<scnRidCyberwareAnimSetSRRefId>;
  public native let deformationAnimSets: array<scnRidDeformationAnimSetSRRefId>;
  public native let bodyCinematicAnimSets: array<scnCinematicAnimSetSRRefId>;
  public native let facialCinematicAnimSets: array<scnCinematicAnimSetSRRefId>;
  public native let cyberwareCinematicAnimSets: array<scnCinematicAnimSetSRRefId>;
  public native let dynamicAnimSets: array<scnDynamicAnimSetSRRefId>;
  public native let holocallInitScn: ResourceAsyncRef; // raRef<CResource>
  public native let actorName: String;
  public native let specCharacterRecordId: TweakDBID;
  public native let specAppearance: CName;
}
