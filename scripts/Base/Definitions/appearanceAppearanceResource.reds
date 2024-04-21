public native class appearanceAppearanceResource extends resStreamedResource {
  native let alternateAppearanceSettingName: CName;
  native let alternateAppearanceSuffixes: array<CName>;
  native let alternateAppearanceMapping: array<appearanceAlternateAppearanceEntry>;
  native let censorshipMapping: array<appearanceCensorshipEntry>;
  native let DismWoundConfig: entdismembermentWoundsConfigSet;
  native let baseType: CName;
  native let baseEntityType: CName;
  native let baseEntity: ResourceAsyncRef; // raRef<entEntityTemplate>
  native let partType: CName;
  native let preset: CName;
  native let commonCookData: ResourceAsyncRef; // raRef<appearanceCookedAppearanceData>
  native let proxyPolyCount: Int32;
  native let forceCompileProxy: Bool;
  native let generatePlayerBlockingCollisionForProxy: Bool;
}
