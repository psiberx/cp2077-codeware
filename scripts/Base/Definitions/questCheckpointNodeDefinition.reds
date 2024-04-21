public native class questCheckpointNodeDefinition extends questSignalStoppingNodeDefinition {
  native let saveLock: Bool;
  native let ignoreSaveLocks: Bool;
  native let pointOfNoReturn: Bool;
  native let endGameSave: Bool;
  native let retryOnFailure: Bool;
  native let additionalEndGameRewardsTweak: array<TweakDBID>;
  native let debugString: String;
}
