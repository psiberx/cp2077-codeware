public native struct scnPropDef {
  public native let propId: scnPropId;
  public native let propName: String;
  public native let specPropRecordId: TweakDBID;
  public native let animSets: array<scnRidAnimSetSRRefId>;
  public native let cinematicAnimSets: array<scnCinematicAnimSetSRRefId>;
  public native let dynamicAnimSets: array<scnDynamicAnimSetSRRefId>;
  public native let entityAcquisitionPlan: scnEntityAcquisitionPlan;
  public native let findEntityInEntityParams: scnFindEntityInEntityParams;
  public native let spawnDespawnParams: scnSpawnDespawnEntityParams;
  public native let spawnSetParams: scnSpawnSetParams;
  public native let communityParams: scnCommunityParams;
  public native let spawnerParams: scnSpawnerParams;
  public native let findEntityInNodeParams: scnFindEntityInNodeParams;
  public native let findEntityInWorldParams: scnFindEntityInWorldParams;
}
