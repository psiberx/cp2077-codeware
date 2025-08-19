public native struct gamePlayerSpawnParams {
  public native let isSpectator: Bool;
  public native let spawnPoint: Transform;
  public native let recordId: TweakDBID;
  public native let gender: CName;
  public native let useSpecifiedStartPoint: Bool;
  public native let spawnTags: redTagList;
  public native let nickname: String;
}
