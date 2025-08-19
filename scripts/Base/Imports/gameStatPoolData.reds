public native struct gameStatPoolData {
  public native let ownerID: StatsObjectID;
  public native let recordID: TweakDBID;
  public native let type: gamedataStatPoolType;
  public native let modifiers: [StatPoolModifier; 2];
  public native let alternativeModifierRecords: [TweakDBID; 2];
  public native let stat: gamedataStatType;
  public native let maxValue: Float;
  public native let customLimitValue: Float;
  public native let changeMode: gameStatPoolDataValueChangeMode;
  public native let bonus: Float;
  public native let bonusType: gameStatPoolDataBonusType;
  public native let currentValue: Float;
  public native let modificationDelay: Float;
  public native let modificationStatus: gameStatPoolDataStatPoolModificationStatus;
}
