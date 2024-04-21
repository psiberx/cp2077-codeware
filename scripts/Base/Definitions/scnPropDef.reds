public native struct scnPropDef {
  native let propId: scnPropId;
  native let propName: String;
  native let specPropRecordId: TweakDBID;
  native let animSets: array<scnRidAnimSetSRRefId>;
  native let cinematicAnimSets: array<scnCinematicAnimSetSRRefId>;
  native let dynamicAnimSets: array<scnDynamicAnimSetSRRefId>;
  native let entityAcquisitionPlan: scnEntityAcquisitionPlan;
  native let findEntityInEntityParams: scnFindEntityInEntityParams;
  native let spawnDespawnParams: scnSpawnDespawnEntityParams;
  native let spawnSetParams: scnSpawnSetParams;
  native let communityParams: scnCommunityParams;
  native let spawnerParams: scnSpawnerParams;
  native let findEntityInNodeParams: scnFindEntityInNodeParams;
  native let findEntityInWorldParams: scnFindEntityInWorldParams;
}
