public native struct gameAreaData {
  native let position: Vector4;
  native let size: Float;
  native let type: gameEAreaType;
  native let shape: gameEAreaShape;
  native let name: CName;
  native let priority: Uint32;
  native let lootID: TweakDBID;
}
