public native struct gamePlayerSpawnParams {
  native let isSpectator: Bool;
  native let spawnPoint: Transform;
  native let recordId: TweakDBID;
  native let gender: CName;
  native let useSpecifiedStartPoint: Bool;
  native let spawnTags: redTagList;
  native let nickname: String;
}
