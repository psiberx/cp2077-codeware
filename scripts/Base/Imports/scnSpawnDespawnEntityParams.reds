public native struct scnSpawnDespawnEntityParams {
  public native let dynamicEntityUniqueName: CName;
  public native let spawnMarker: CName;
  public native let spawnMarkerType: scnMarkerType;
  public native let spawnMarkerNodeRef: NodeRef;
  public native let spawnOffset: Transform;
  public native let itemOwnerId: scnPerformerId;
  public native let specRecordId: TweakDBID;
  public native let appearance: CName;
  public native let spawnOnStart: Bool;
  public native let isEnabled: Bool;
  public native let validateSpawnPostion: Bool;
  public native let alwaysSpawned: Bool;
  public native let keepAlive: Bool;
  public native let findInWorld: Bool;
  public native let forceMaxVisibility: Bool;
  public native let prefetchAppearance: Bool;
}
