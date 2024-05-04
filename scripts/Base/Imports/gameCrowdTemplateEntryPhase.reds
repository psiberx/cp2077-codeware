public native struct gameCrowdTemplateEntryPhase {
  native let phaseName: CName;
  native let timePeriods: array<gameCrowdPhaseTimePeriod>;
  native let density: Float;
  native let charactersData: array<gameCrowdTemplateCharacterData>;
  native let legacy: Bool;
  native let legacyDensityInTimePeriods: Bool;
  native let legacyCharactersData: Bool;
}
