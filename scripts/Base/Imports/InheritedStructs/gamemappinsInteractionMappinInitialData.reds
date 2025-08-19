public native struct gamemappinsInteractionMappinInitialData {
  public native let mappinType: TweakDBID;
  public native let variant: gamedataMappinVariant;
  public native let active: Bool;
  public native let debugCaption: String;
  public native let localizedCaption: LocalizationString;
  public native let visibleThroughWalls: Bool;
  public native let scriptData: ref<MappinScriptData>;
}
