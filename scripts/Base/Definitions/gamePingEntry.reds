public native struct gamePingEntry {
  native let owner: wref<GameObject>;
  native let worldPosition: Vector4;
  native let time: netTime;
  native let pingType: gamedataPingType;
  native let hitObject: wref<Entity>;
}
