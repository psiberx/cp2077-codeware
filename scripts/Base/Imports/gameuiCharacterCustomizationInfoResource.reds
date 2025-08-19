public native class gameuiCharacterCustomizationInfoResource extends CResource {
  public native let version: Uint32;
  public native let headCustomizationOptions: array<ref<gameuiCharacterCustomizationInfo>>;
  public native let bodyCustomizationOptions: array<ref<gameuiCharacterCustomizationInfo>>;
  public native let armsCustomizationOptions: array<ref<gameuiCharacterCustomizationInfo>>;
  public native let armsGroups: array<gameuiOptionsGroup>;
  public native let headGroups: array<gameuiOptionsGroup>;
  public native let bodyGroups: array<gameuiOptionsGroup>;
  public native let perspectiveInfo: array<gameuiPerspectiveInfo>;
  public native let uiPresets: array<gameuiCharacterCustomizationUiPresetInfo>;
  public native let excludedFromRandomize: array<CName>;
  public native let versionUpdateInfo: array<gameuiCharacterCustomizationVersionUpdateInfo>;
}
