public native struct gameStatPoolData {
  native let ownerID: StatsObjectID;
  native let recordID: TweakDBID;
  native let type: gamedataStatPoolType;
  native let stat: gamedataStatType;
  native let maxValue: Float;
  native let customLimitValue: Float;
  native let changeMode: gameStatPoolDataValueChangeMode;
  native let bonus: Float;
  native let bonusType: gameStatPoolDataBonusType;
  native let currentValue: Float;
  native let modificationDelay: Float;
  native let modificationStatus: gameStatPoolDataStatPoolModificationStatus;
}
