public native struct gamemappinsInteractionMappinInitialData {
  native let mappinType: TweakDBID;
  native let variant: gamedataMappinVariant;
  native let active: Bool;
  native let debugCaption: String;
  native let localizedCaption: LocalizationString;
  native let visibleThroughWalls: Bool;
  native let scriptData: ref<MappinScriptData>;
}
