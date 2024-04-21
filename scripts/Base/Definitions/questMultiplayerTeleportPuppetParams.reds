public native struct questMultiplayerTeleportPuppetParams {
  native let teleportAllPlayers: Bool;
  native let spawnPointTag: CName;
  native let destinationRef: EntityReference;
  native let destinationOffset: Vector3;
  native let areaNodeTriggerRef: EntityReference;
}
