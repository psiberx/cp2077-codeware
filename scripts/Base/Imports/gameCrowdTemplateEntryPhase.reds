public native struct gameCrowdTemplateEntryPhase {
  public native let phaseName: CName;
  public native let timePeriods: array<gameCrowdPhaseTimePeriod>;
  public native let density: Float;
  public native let charactersData: array<gameCrowdTemplateCharacterData>;
  public native let legacy: Bool;
  public native let legacyDensityInTimePeriods: Bool;
  public native let legacyCharactersData: Bool;
}
