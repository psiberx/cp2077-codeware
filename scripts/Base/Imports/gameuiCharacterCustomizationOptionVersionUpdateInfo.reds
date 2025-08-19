public native struct gameuiCharacterCustomizationOptionVersionUpdateInfo {
  public native let curOptionNames: array<CName>;
  public native let curDefintionName: CName;
  public native let optionPrereqs: array<gameuiCharacterCustomizationOptionVersionPrereq>;
  public native let newOptionName: CName;
  public native let newDefinitionName: CName;
  public native let replaceCurOption: Bool;
}
