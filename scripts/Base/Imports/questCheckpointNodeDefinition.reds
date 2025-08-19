public native class questCheckpointNodeDefinition extends questSignalStoppingNodeDefinition {
  public native let saveLock: Bool;
  public native let ignoreSaveLocks: Bool;
  public native let pointOfNoReturn: Bool;
  public native let endGameSave: Bool;
  public native let retryOnFailure: Bool;
  public native let additionalEndGameRewardsTweak: array<TweakDBID>;
  public native let debugString: String;
}
