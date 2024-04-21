public native class gameuiCharacterCustomizationInfoResource extends CResource {
  native let version: Uint32;
  native let headCustomizationOptions: array<ref<gameuiCharacterCustomizationInfo>>;
  native let bodyCustomizationOptions: array<ref<gameuiCharacterCustomizationInfo>>;
  native let armsCustomizationOptions: array<ref<gameuiCharacterCustomizationInfo>>;
  native let armsGroups: array<gameuiOptionsGroup>;
  native let headGroups: array<gameuiOptionsGroup>;
  native let bodyGroups: array<gameuiOptionsGroup>;
  native let perspectiveInfo: array<gameuiPerspectiveInfo>;
  native let uiPresets: array<gameuiCharacterCustomizationUiPresetInfo>;
  native let excludedFromRandomize: array<CName>;
  native let versionUpdateInfo: array<gameuiCharacterCustomizationVersionUpdateInfo>;
}
