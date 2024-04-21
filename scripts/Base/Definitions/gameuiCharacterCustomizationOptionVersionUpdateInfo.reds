public native struct gameuiCharacterCustomizationOptionVersionUpdateInfo {
  native let curOptionNames: array<CName>;
  native let curDefintionName: CName;
  native let optionPrereqs: array<gameuiCharacterCustomizationOptionVersionPrereq>;
  native let newOptionName: CName;
  native let newDefinitionName: CName;
  native let replaceCurOption: Bool;
}
