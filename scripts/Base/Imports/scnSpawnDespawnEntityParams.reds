public native struct scnSpawnDespawnEntityParams {
  native let dynamicEntityUniqueName: CName;
  native let spawnMarker: CName;
  native let spawnMarkerType: scnMarkerType;
  native let spawnMarkerNodeRef: NodeRef;
  native let spawnOffset: Transform;
  native let itemOwnerId: scnPerformerId;
  native let specRecordId: TweakDBID;
  native let appearance: CName;
  native let spawnOnStart: Bool;
  native let isEnabled: Bool;
  native let validateSpawnPostion: Bool;
  native let alwaysSpawned: Bool;
  native let keepAlive: Bool;
  native let findInWorld: Bool;
  native let forceMaxVisibility: Bool;
  native let prefetchAppearance: Bool;
}
